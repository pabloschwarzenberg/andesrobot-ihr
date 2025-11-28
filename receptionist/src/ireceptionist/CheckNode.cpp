#include "CheckNode.hpp"

NodeStatus CheckNode::tick()
{
    auto node = rclcpp::Node::make_shared("node_checker");
    Expected<std::string> target_node_name = getInput<std::string>("node");
    if(!target_node_name)
    {
        throw RuntimeError("missing required input [node]: ", 
                                target_node_name.error() );
    }
    std::vector<std::string> node_names = node->get_node_names();

    auto it = std::find(node_names.begin(), node_names.end(), target_node_name.value());
    if (it != node_names.end())
    {
        return NodeStatus::SUCCESS;
    }
    else
    {
        std::cout << "Node unavailable: " << target_node_name.value() << std::endl;
        return NodeStatus::FAILURE;
    }
}