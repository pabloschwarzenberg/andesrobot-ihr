import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node
from subprocess import call

from nlp_interfaces.action import Talk

class TalkActionServer(Node):

    def __init__(self):
        super().__init__('talk_action_server')
        self._action_server = ActionServer(
            self,
            Talk,
            'Talk',
            self.execute_callback)

    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')
        call(["espeak-ng","-v","mb-us2","-s","128",goal_handle.request.speech]) 
        goal_handle.succeed()
        result = Talk.Result()
        return result


def main(args=None):
    rclpy.init(args=args)

    talk_action_server = TalkActionServer()

    rclpy.spin(talk_action_server)


if __name__ == '__main__':
    main()
