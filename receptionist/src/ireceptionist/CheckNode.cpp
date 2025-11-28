#include "CheckNode.hpp"

NodeStatus CheckNode::tick()
{
    auto node = rclcpp::Node::make_shared("node_checker");
    std::string target_node_name = getInput<std::string>("name");
    std::vector<std::string> node_names = node->get_node_names();

    auto it = std::find(node_names.begin(), node_names.end(), target_node_name);
    if (it != node_names.end())
    {
        return NodeStatus::SUCCESS;
    }
    else
    {
        return NodeStatus::FAILURE;
    }
}