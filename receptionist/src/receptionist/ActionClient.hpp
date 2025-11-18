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
  explicit TalkActionClient(const rclcpp::NodeOptions & options)
  : Node("talk_action_client", options)
  {
    this->client_ptr = rclcpp_action::create_client<nlp_interfaces::action::Talk>(
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
  rclcpp_action::Client<nlp_interfaces::action::Talk>::SharedPtr client_ptr;
  rclcpp::TimerBase::SharedPtr timer;
  bool finished;

  void goal_response_callback(std::shared_future<rclcpp_action::ClientGoalHandle<nlp_interfaces::action::Talk>::SharedPtr> future);
  
  void result_callback(const rclcpp_action::ClientGoalHandle<nlp_interfaces::action::Talk>::WrappedResult & result);
};