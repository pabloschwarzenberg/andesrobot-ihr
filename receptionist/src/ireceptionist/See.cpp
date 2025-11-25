#include "See.hpp"

#include <behaviortree_ros2/bt_action_node.hpp>

using namespace BT;

bool See::setGoal(RosActionNode::Goal& goal)
{
  getInput("number", goal.number);
  return true;
}

NodeStatus See::onResultReceived(const WrappedResult& wr)
{
  std::cout << (int)wr.result->found << std::endl;
  return NodeStatus::SUCCESS;
}

NodeStatus See::onFailure(ActionNodeErrorCode error)
{
  return NodeStatus::FAILURE;
}

NodeStatus See::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  std::cout << (int)feedback->progress << std::endl;
  return NodeStatus::RUNNING;
}