#include "Ask.hpp"
#include <functional>
#include <memory>
#include <thread>

#include <behaviortree_ros2/bt_action_node.hpp>

using namespace BT;

  // This is called when the TreeNode is ticked and it should
  // send the request to the action server
  bool Ask::setGoal(RosActionNode::Goal& goal)
  {
    getInput("speech", goal.speech);
    // return true, if we were able to set the goal correctly.
    return true;
  }

  // Callback executed when the reply is received.
  // Based on the reply you may decide to return SUCCESS or FAILURE.
  NodeStatus Ask::onResultReceived(const WrappedResult& wr)
  {
    return NodeStatus::SUCCESS;
  }

  // Callback invoked when there was an error at the level
  // of the communication between client and server.
  // This will set the status of the TreeNode to either SUCCESS or FAILURE,
  // based on the return value.
  // If not overridden, it will return FAILURE by default.
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
