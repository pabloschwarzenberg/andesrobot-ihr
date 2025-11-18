#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>

#include "nlp_interfaces/action/talk.hpp"

#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

using ITalk = nlp_interfaces::action::Talk;
using GoalHandleITalk = rclcpp_action::ClientGoalHandle<ITalk>;

class TalkActionClient : public rclcpp::Node
{
public:
  explicit TalkActionClient(const rclcpp::NodeOptions & options)
  : Node("talk_action_client", options)
  {
    this->client_ptr = rclcpp_action::create_client<ITalk>(
      this,
      "talk");

    this->timer = this->create_wall_timer(
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
  rclcpp_action::Client<ITalk>::SharedPtr client_ptr;
  rclcpp::TimerBase::SharedPtr timer;
  bool finished;

  void goal_response_callback(GoalHandleITalk::SharedPtr future);

  void feedback_callback(GoalHandleITalk::SharedPtr,const std::shared_ptr<const ITalk::Feedback> feedback);
  
  void result_callback(const GoalHandleITalk::WrappedResult & result);
};
