#include <functional>
#include <memory>
#include <thread>

#include "vision_interfaces/action/find_person.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

#include <opencv2/opencv.hpp>
#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>

namespace vision_actions
{  
  class FindPersonActionServer : public rclcpp::Node
  {
  public:
    using IFindPerson = vision_interfaces::action::FindPerson;
    using GoalHandleIFindPerson = rclcpp_action::ServerGoalHandle<IFindPerson>;

    explicit FindPersonActionServer(const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
    : Node("findperson_action_server", options)
    {
      using namespace std::placeholders;

      this->action_server_ = rclcpp_action::create_server<IFindPerson>(
        this,
        "findperson",
        std::bind(&FindPersonActionServer::handle_goal, this, _1, _2),
        std::bind(&FindPersonActionServer::handle_cancel, this, _1),
        std::bind(&FindPersonActionServer::handle_accepted, this, _1));
    }

  private:
    rclcpp_action::Server<IFindPerson>::SharedPtr action_server_;

    rclcpp_action::GoalResponse handle_goal(
      const rclcpp_action::GoalUUID & uuid,
      std::shared_ptr<const IFindPerson::Goal> goal)
    {
      RCLCPP_INFO(this->get_logger(), "Received goal request %d", goal->number);
      (void)uuid;
      return rclcpp_action::GoalResponse::ACCEPT_AND_EXECUTE;
    }

    rclcpp_action::CancelResponse handle_cancel(
      const std::shared_ptr<GoalHandleIFindPerson> goal_handle)
    {
      RCLCPP_INFO(this->get_logger(), "Received request to cancel goal");
      (void)goal_handle;
      return rclcpp_action::CancelResponse::ACCEPT;
    }

    void handle_accepted(const std::shared_ptr<GoalHandleIFindPerson> goal_handle)
    {
      using namespace std::placeholders;
      // this needs to return quickly to avoid blocking the executor, so spin up a new thread
      std::thread{std::bind(&FindPersonActionServer::execute, this, _1), goal_handle}.detach();
    }

    void execute(const std::shared_ptr<GoalHandleIFindPerson> goal_handle)
    {
      RCLCPP_INFO(this->get_logger(), "Executing goal");
      rclcpp::Rate loop_rate(1);
      const auto goal = goal_handle->get_goal();
      auto feedback = std::make_shared<IFindPerson::Feedback>();
      feedback->progress=0;
      auto result = std::make_shared<IFindPerson::Result>();
      int i;

      if (goal_handle->is_canceling())
      {
          result->found = 0;
          goal_handle->canceled(result);
          RCLCPP_INFO(this->get_logger(), "Goal canceled");
          return;
      }

	    std::string modelPath = "face_detection_yunet_2023mar.onnx";
      cv::Ptr<cv::FaceDetectorYN> detector = cv::FaceDetectorYN::create(modelPath, "", cv::Size(320, 240));
      if (detector.empty())
      {
        goal_handle->abort(result);
        RCLCPP_INFO(this->get_logger(), "Failed to load YuNet model.");
		    return;
      }

	    cv::VideoCapture cap(0);
	    if(!cap.isOpened())
	    {
        result->found = 0;
        goal_handle->abort(result);
        RCLCPP_INFO(this->get_logger(), "Could not open camera");
		    return;
	    }
	    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
      cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);
	    cv::Mat frame;
      cv::Mat faces;

      for(i=0;i<5;i++)
      {
        cap >> frame;
        if (frame.empty())
        {
          result->found = 0;
          goal_handle->abort(result);
          RCLCPP_INFO(this->get_logger(), "Blank frame grabbed.");
          break;
        }	
        detector->setInputSize(frame.size());
        detector->detect(frame, faces);
        if(faces.rows!=0)
        {
          result->found=faces.rows;
          break;
        }
        else
        {
          result->found=0;
          feedback->progress=i+1;
        }
        goal_handle->publish_feedback(feedback);
        RCLCPP_INFO(this->get_logger(), "Publish feedback");

        loop_rate.sleep();
      }
      cap.release();

      if (rclcpp::ok())
      {
          goal_handle->succeed(result);
          RCLCPP_INFO(this->get_logger(), "Goal succeeded");
      }
    }
  };
};

RCLCPP_COMPONENTS_REGISTER_NODE(vision_actions::FindPersonActionServer)
