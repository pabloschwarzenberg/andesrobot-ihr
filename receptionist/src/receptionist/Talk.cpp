#include "Talk.hpp"
#include <functional>
#include <memory>
#include <thread>

#include "nlp_interfaces/action/talk.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp_action/rclcpp_action.hpp"
#include "rclcpp_components/register_node_macro.hpp"

NodeStatus Talk::onStart()
{
  if(!getInput<std::string>("speech",goal))
  {
    throw BT::RuntimeError("missing required input [speech]");
  }
  return NodeStatus::RUNNING;
}

NodeStatus Talk::onRunning()
{
  std::cout << "Robot says: " << goal << std::endl;
  return NodeStatus::SUCCESS;
}

void Talk::onHalted()
{
  printf("Talk: ABORTED");
}

NodeStatus Greet::onRunning()
{
  return Talk::onRunning();
}

NodeStatus Ask::onRunning()
{
  return Talk::onRunning();
}
