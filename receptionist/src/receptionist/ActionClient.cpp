#include <functional>
#include <future>
#include <memory>
#include <string>
#include <sstream>
#include "ActionClient.hpp"

void TalkActionClient::send_goal()
{
    using namespace std::placeholders;

    this->timer->cancel();

    if (!this->client_ptr->wait_for_action_server()) {
      RCLCPP_ERROR(this->get_logger(), "Action server not available after waiting");
      rclcpp::shutdown();
    }

    auto goal_msg = nlp_interfaces::action::Talk::Goal();
    goal_msg.speech = "Hello";

    RCLCPP_INFO(this->get_logger(), "Sending goal");

    auto send_goal_options = rclcpp_action::Client<nlp_interfaces::action::Talk>::SendGoalOptions();
    send_goal_options.goal_response_callback =
      std::bind(&TalkActionClient::goal_response_callback, this, _1);

    send_goal_options.result_callback =
      std::bind(&TalkActionClient::result_callback, this, _1);
    this->client_ptr_->async_send_goal(goal_msg, send_goal_options);
}

void TalkActionClient::goal_response_callback(
    std::shared_future<rclcpp_action::ClientGoalHandle<nlp_interfaces::action::Talk>::SharedPtr> future)
{
    auto goal_handle = future.get();
    if (!goal_handle) {
      RCLCPP_ERROR(this->get_logger(), "Goal was rejected by server");
    } else {
      RCLCPP_INFO(this->get_logger(), "Goal accepted by server, waiting for result");
    }
}

void TalkActionClient::result_callback(const rclcpp_action::ClientGoalHandle<nlp_interfaces::action::Talk>::WrappedResult & result)
{
    finished=true;

    switch (result.code) {
      case rclcpp_action::ResultCode::SUCCEEDED:
        break;
      case rclcpp_action::ResultCode::ABORTED:
        RCLCPP_ERROR(this->get_logger(), "Goal was aborted");
        return;
      case rclcpp_action::ResultCode::CANCELED:
        RCLCPP_ERROR(this->get_logger(), "Goal was canceled");
        return;
      default:
        RCLCPP_ERROR(this->get_logger(), "Unknown result code");
        return;
    }
    std::stringstream ss;
    ss << "Talk Action Finished";

    RCLCPP_INFO(this->get_logger(), ss.str().c_str());
    rclcpp::shutdown();
}

RCLCPP_COMPONENTS_REGISTER_NODE(TalkActionClient)