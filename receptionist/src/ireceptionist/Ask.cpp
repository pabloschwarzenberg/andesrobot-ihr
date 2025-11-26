#include "Ask.hpp"
#include <functional>
#include <memory>
#include <thread>

#include <behaviortree_ros2/bt_action_node.hpp>

using namespace BT;

bool Ask::setGoal(RosActionNode::Goal& goal)
{
  getInput("speech", goal.speech);
  return true;
}

NodeStatus Ask::onResultReceived(const WrappedResult& wr)
{
  return NodeStatus::SUCCESS;
}

NodeStatus Ask::onFailure(ActionNodeErrorCode error)
{
  return NodeStatus::FAILURE;
}

  // we also support a callback for the feedback, as in
  // the original tutorial.
  // Usually, this callback should return RUNNING, but you
  // might decide, based on the value of the feedback, to abort
  // the action, and consider the TreeNode completed.
  // In that case, return SUCCESS or FAILURE.
  // The Cancel request will be send automatically to the server.
NodeStatus Ask::onFeedback(const std::shared_ptr<const Feedback> feedback)
{
  return NodeStatus::RUNNING;
}