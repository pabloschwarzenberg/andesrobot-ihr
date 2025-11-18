#include "behaviortree_cpp_v3/bt_factory.h"
#include "Talk.hpp"
#include "MoveTo.hpp"
#include "Remember.hpp"
#include "See.hpp"

using namespace BT;

// Simple function that return a NodeStatus
BT::NodeStatus CheckBattery()
{
  std::cout << "[ Battery: OK ]" << std::endl;
  return BT::NodeStatus::SUCCESS;
}

// We want to wrap into an ActionNode the methods open() and close()
class GripperInterface
{
public:
  GripperInterface(): _open(true) {}

  NodeStatus open()
  {
    _open = true;
    std::cout << "GripperInterface::open" << std::endl;
    return NodeStatus::SUCCESS;
  }

  NodeStatus close()
  {
    std::cout << "GripperInterface::close" << std::endl;
    _open = false;
    return NodeStatus::SUCCESS;
  }

private:
  bool _open; // shared information
};

int main()
{
    // We use the BehaviorTreeFactory to register our custom nodes
  BehaviorTreeFactory factory;

  factory.registerNodeType<MoveTo>("MoveTo");
  factory.registerNodeType<See>("See");
  factory.registerNodeType<Greet>("Greet");
  factory.registerNodeType<Ask>("Ask");
  factory.registerNodeType<Remember>("Remember");

  // Registering a SimpleActionNode using a function pointer.
  // You can use C++11 lambdas or std::bind
  factory.registerSimpleCondition("CheckBattery", [&](TreeNode&) { return CheckBattery(); });

  //You can also create SimpleActionNodes using methods of a class
  GripperInterface gripper;
  factory.registerSimpleAction("MoveTo", [&](TreeNode&){ return gripper.open(); } );
  factory.registerSimpleAction("Talk", [&](TreeNode&){ return gripper.close(); } );

  // Trees are created at deployment-time (i.e. at run-time, but only
  // once at the beginning).

  // IMPORTANT: when the object "tree" goes out of scope, all the
  // TreeNodes are destroyed
   auto tree = factory.createTreeFromFile("./receptionist.xml");

  // To "execute" a Tree you need to "tick" it.
  // The tick is propagated to the children based on the logic of the tree.
  // In this case, the entire sequence is executed, because all the children
  // of the Sequence return SUCCESS.
  tree.tickRootWhileRunning();

  return 0;
}
