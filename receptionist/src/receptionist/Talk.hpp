#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

// SyncActionNode (synchronous action) with an input port.
class Talk : public StatefulActionNode
{
public:
  // If your Node has ports, you must use this constructor signature 
  Talk(const std::string& name, const NodeConfiguration& config)
    : StatefulActionNode(name, config)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    return { InputPort<std::string>("speech") };
  }

  // Override the virtual function tick()
  NodeStatus onStart() override;

  NodeStatus onRunning() override;

  void onHalted() override;

protected:
  std::string goal;
};

// SyncActionNode (synchronous action) with an input port.
class Greet : public Talk
{
public:
  // If your Node has ports, you must use this constructor signature 
  Greet(const std::string& name, const NodeConfiguration& config)
    : Talk(name, config)
  { }

  NodeStatus onRunning() override;
};

// SyncActionNode (synchronous action) with an input port.
class Ask : public Talk
{
public:
  // If your Node has ports, you must use this constructor signature 
  Ask(const std::string& name, const NodeConfiguration& config)
    : Talk(name, config)
  { }

  NodeStatus onRunning() override;
};
