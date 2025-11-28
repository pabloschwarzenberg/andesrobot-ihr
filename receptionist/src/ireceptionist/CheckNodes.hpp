#include <behaviortree_cpp/condition_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <vector>
#include <algorithm>

using namespace BT;

class CheckNodes : public ConditionNode
{
    public:
        CheckNodes(const std::string& name, const NodeConfiguration& config)
            : ConditionNode(name, config)
        {
            //rclcpp::init(0, nullptr);
        };

        NodeStatus tick() override;
};
