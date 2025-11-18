import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node
from espeak_ng import espeak_AUDIO_OUTPUT
import espeak_ng
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
#        espeak_ng.initialize(output=espeak_AUDIO_OUTPUT.AUDIO_OUTPUT_SYNCH_PLAYBACK)
#        espeak_ng.set_voice_by_properties(name="mb-us2")
#        espeak_ng.synth(goal_handle.request.speech)
        call(["espeak-ng","-v","mb-us2",goal_handle.request.speech]) 
        goal_handle.succeed()
        result = Talk.Result()
        return result


def main(args=None):
    rclpy.init(args=args)

    talk_action_server = TalkActionServer()

    rclpy.spin(talk_action_server)


if __name__ == '__main__':
    main()
