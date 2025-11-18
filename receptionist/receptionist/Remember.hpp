#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

// SyncActionNode (synchronous action) with an input port.
class Remember : public SyncActionNode
{
public:
  // If your Node has ports, you must use this constructor signature 
  Remember(const std::string& name, const NodeConfiguration& config)
    : SyncActionNode(name, config)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    // This action has a single input port called "message"
    return { InputPort<std::string>("object") };
  }

  // Override the virtual function tick()
  NodeStatus tick() override;
};