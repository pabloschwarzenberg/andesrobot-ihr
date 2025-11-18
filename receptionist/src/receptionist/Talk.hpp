#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

// SyncActionNode (synchronous action) with an input port.
class Talk : public SyncActionNode
{
public:
  // If your Node has ports, you must use this constructor signature 
  Talk(const std::string& name, const NodeConfiguration& config)
    : SyncActionNode(name, config)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    // This action has a single input port called "message"
    return { InputPort<std::string>("speech") };
  }

  // Override the virtual function tick()
  NodeStatus tick() override;
};

// SyncActionNode (synchronous action) with an input port.
class Greet : public Talk
{
public:
  // If your Node has ports, you must use this constructor signature 
  Greet(const std::string& name, const NodeConfiguration& config)
    : Talk(name, config)
  { }

  // Override the virtual function tick()
  NodeStatus tick() override;
};

// SyncActionNode (synchronous action) with an input port.
class Ask : public Talk
{
public:
  // If your Node has ports, you must use this constructor signature 
  Ask(const std::string& name, const NodeConfiguration& config)
    : Talk(name, config)
  { }

  // Override the virtual function tick()
  NodeStatus tick() override;
};
