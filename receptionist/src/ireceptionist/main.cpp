#include "behaviortree_cpp/bt_factory.h"
#include "Talk.hpp"
#include "Ask.hpp"
#include "MoveTo.hpp"
#include "Remember.hpp"
#include "See.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rclcpp/executors.hpp"

using namespace BT;

int main(int argc, char** argv)
{
  rclcpp::init(argc,argv);
    // We use the BehaviorTreeFactory to register our custom nodes
  BehaviorTreeFactory factory;

  factory.registerNodeType<MoveTo>("MoveTo");
  factory.registerNodeType<See>("See");

  auto node = std::make_shared<rclcpp::Node>("talk_action_client");
  RosNodeParams params;
  params.nh = node;
  params.default_port_value = "Talk";
  factory.registerNodeType<Talk>("Talk",params);

  auto node2 = std::make_shared<rclcpp::Node>("ask_action_client");
  RosNodeParams params2;
  params2.nh = node2;
  params2.default_port_value = "Ask";
  factory.registerNodeType<Ask>("Ask",params2);
  
  factory.registerNodeType<Remember>("Remember");

   auto tree = factory.createTreeFromFile("./receptionist.xml");

  // To "execute" a Tree you need to "tick" it.
  // The tick is propagated to the children based on the logic of the tree.
  // In this case, the entire sequence is executed, because all the children
  // of the Sequence return SUCCESS.
  tree.tickWhileRunning();

  return 0;
}
