#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include <behaviortree_ros2/bt_action_node.hpp>
#include "nlp_interfaces/action/talk.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using ITalk = nlp_interfaces::action::Talk;
using GoalHandleITalk = rclcpp_action::ClientGoalHandle<ITalk>;

using namespace BT;

class Talk : public RosActionNode<ITalk>
{
public:
  Talk(const std::string& name, const NodeConfiguration& config,
		  const RosNodeParams& params)
    : RosActionNode(name, config, params)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    return { InputPort<std::string>("speech") };
  }

  bool setGoal(RosActionNode::Goal& goal) override;

  NodeStatus onResultReceived(const WrappedResult& wr) override;

  virtual NodeStatus onFailure(ActionNodeErrorCode error) override;

  NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback);
};
