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
  NodeStatus tick() override
  {
    Optional<std::string> msg = getInput<std::string>("speech");
    // Check if optional is valid. If not, throw its error
    if (!msg)
    {
      throw BT::RuntimeError("missing required input [message]: ", 
                              msg.error() );
    }
    // use the method value() to extract the valid message.
    std::cout << "Robot says: " << msg.value() << std::endl;
    return NodeStatus::SUCCESS;
  }
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
  NodeStatus tick() override
  {
    return Talk::tick();
  }
};
