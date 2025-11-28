#include <behaviortree_cpp/condition_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <vector>
#include <algorithm>

class CheckNodes : public BT::ConditionNode
{
    public:
        CheckNodes(const std::string& name, const BT::NodeConfiguration& config)
            : BT::CheckNodes(name, config)
        {
            //rclcpp::init(0, nullptr);
        };

        BT::NodeStatus tick() override;
};
