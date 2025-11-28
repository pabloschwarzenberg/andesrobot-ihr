#include <behaviortree_cpp/condition_node.h>
#include <rclcpp/rclcpp.hpp>
#include <string>
#include <vector>
#include <algorithm>

using namespace BT;

class CheckNode : public ConditionNode
{
    public:
        CheckNode(const std::string& name, const NodeConfiguration& config)
            : ConditionNode(name, config)
        {
            //rclcpp::init(0, nullptr);
        };

        static PortsList providedPorts()
        {
            return { InputPort<std::string>("node") };
        }

        NodeStatus tick() override;
};
