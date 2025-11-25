#include "rclcpp/rclcpp.hpp"
#include "behaviortree_cpp/bt_factory.h"
#include <behaviortree_ros2/bt_action_node.hpp>
#include "vision_interfaces/action/find_person.hpp"

using namespace BT;

using IFindPerson = vision_interfaces::action::FindPerson;
using GoalHandleIFindPerson = rclcpp_action::ClientGoalHandle<IFindPerson>;

// SyncActionNode (synchronous action) with an input port.
class See : public RosActionNode<IFindPerson>
{
public:
  See(const std::string& name, const NodeConfiguration& config,
		  const RosNodeParams& params)
    : RosActionNode(name, config, params)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    // This action has a single input port called "message"
    return { InputPort<std::string>("object") };
  }

  bool setGoal(RosActionNode::Goal& goal) override;

  NodeStatus onResultReceived(const WrappedResult& wr) override;

  virtual NodeStatus onFailure(ActionNodeErrorCode error) override;

  NodeStatus onFeedback(const std::shared_ptr<const Feedback> feedback);
};
