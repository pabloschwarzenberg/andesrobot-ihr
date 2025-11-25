#include <functional>
#include <memory>
#include <thread>

#include "vision_interfaces/action/findperson.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

class FindPersonActionServer : public rclcpp::Node
{
public:
  using IFindPerson = action::FindPerson;
  using GoalHandleIFindPerson = rclcpp_action::ServerGoalHandle<IFindPerson>;

  ACTION_TUTORIALS_CPP_PUBLIC
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
    auto feedback = std::make_shared<FindPerson::Feedback>();
    feedback->status=0;
    auto result = std::make_shared<Fibonacci::Result>();

    if (goal_handle->is_canceling())
    {
        result->found = 0;
        goal_handle->canceled(result);
        RCLCPP_INFO(this->get_logger(), "Goal canceled");
        return;
    }
    
    goal_handle->publish_feedback(feedback);
    RCLCPP_INFO(this->get_logger(), "Publish feedback");

    //loop_rate.sleep();

    if (rclcpp::ok())
    {
        result->found = 1;
        goal_handle->succeed(result);
        RCLCPP_INFO(this->get_logger(), "Goal succeeded");
    }
};

RCLCPP_COMPONENTS_REGISTER_NODE(FindPersonActionServer)