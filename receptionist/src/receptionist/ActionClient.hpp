#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "nlp_interfaces/action/talk.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

class TalkActionClient : public rclcpp::Node
{
public:
  using Talk = nlp_interfaces::action::Talk;
  using GoalHandleTalk = rclcpp_action::ClientGoalHandle<Talk>;

  explicit TalkActionClient(const rclcpp::NodeOptions & options)
  : Node("talk_action_client", options)
  {
    this->client_ptr_ = rclcpp_action::create_client<Talk>(
      this,
      "talk");

    this->timer_ = this->create_wall_timer(
      std::chrono::milliseconds(500),
      std::bind(&TalkActionClient::send_goal, this));

    finished=false;
  }

  bool isFinished()
  {
    return finished;
  }

  void send_goal();

private:
  rclcpp_action::Client<Talk>::SharedPtr client_ptr_;
  rclcpp::TimerBase::SharedPtr timer_;
  bool finished;

  void goal_response_callback(std::shared_future<GoalHandleTalk::SharedPtr> future);

  void feedback_callback(GoalHandleTalk::SharedPtr,
    const std::shared_ptr<const Talk::Feedback> feedback)
  
  void result_callback(const GoalHandleTalk::WrappedResult & result);
};