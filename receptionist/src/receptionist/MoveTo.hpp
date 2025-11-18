#include "behaviortree_cpp_v3/bt_factory.h"

using namespace BT;

struct Position2D 
{ 
  double x;
  double y; 
};

namespace BT
{
    template <> inline Position2D convertFromString(StringView str)
    {
        // We expect real numbers separated by semicolons
        auto parts = splitString(str, ';');
        if (parts.size() != 2)
        {
            throw RuntimeError("invalid input)");
        }
        else
        {
            Position2D output;
            output.x     = convertFromString<double>(parts[0]);
            output.y     = convertFromString<double>(parts[1]);
            return output;
        }
    }
}

// SyncActionNode (synchronous action) with an input port.
class MoveTo : public SyncActionNode
{
public:
  // If your Node has ports, you must use this constructor signature 
  MoveTo(const std::string& name, const NodeConfiguration& config)
    : SyncActionNode(name, config)
  { }

  // It is mandatory to define this STATIC method.
  static PortsList providedPorts()
  {
    // This action has a single input port called "message"
    return { InputPort<Position2D>("location") };
  }

  // Override the virtual function tick()
  NodeStatus tick() override;
};
