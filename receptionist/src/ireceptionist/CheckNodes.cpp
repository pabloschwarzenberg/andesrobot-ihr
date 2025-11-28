#include "CheckNodes.hpp"

BT::NodeStatus CheckNodes::tick()
{
    auto node = rclcpp::Node::make_shared("node_checker");
    std::string target_node_name = "findperson_action";

    std::vector<std::string> node_names = node->get_node_names();

    auto it = std::find(node_names.begin(), node_names.end(), target_node_name);
    if (it != node_names.end())
    {
        return BT::NodeStatus::SUCCESS;
    }
    else
    {
        return BT::NodeStatus::FAILURE;
    }
}