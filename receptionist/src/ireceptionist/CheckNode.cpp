#include "CheckNode.hpp"

NodeStatus CheckNode::tick()
{
    auto node = rclcpp::Node::make_shared("node_checker");
    std::vector<std::string> node_names = node->get_node_names();

    auto it = std::find(node_names.begin(), node_names.end(), getInput<std::string>("name"));
    if (it != node_names.end())
    {
        return NodeStatus::SUCCESS;
    }
    else
    {
        return NodeStatus::FAILURE;
    }
}