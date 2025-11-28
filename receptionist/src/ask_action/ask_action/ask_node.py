import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node
from subprocess import call
import queue, sys, sounddevice as sd
from vosk import Model, KaldiRecognizer
import json

from nlp_interfaces.action import Ask

def listen_callback(indata, frames, time, status):
    if status:
        print(status, file=sys.stderr)
    AskActionServer.Q.put(bytes(indata))

class AskActionServer(Node):
    Q = queue.Queue()

    def __init__(self):
        super().__init__('ask_action_server')
        self._action_server = ActionServer(
            self,
            Ask,
            'Ask',
            self.execute_callback)
        self.model = Model("./vosk-model-small-en-us-0.15")
        
    def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')
        call(["espeak-ng","-v","mb-us2","-s","128",goal_handle.request.speech])

        samplerate = int(sd.query_devices(None, "input")["default_samplerate"])
        rec = KaldiRecognizer(self.model, samplerate)
        with sd.RawInputStream(samplerate=samplerate, blocksize=4000, dtype="int16", channels=1, callback=listen_callback):
            while True:
                data = AskActionServer.Q.get()
                if rec.AcceptWaveform(data):
                    response=json.loads(rec.Result())
                    print(response.get("text"))
                    break

        goal_handle.succeed()
        result = Ask.Result()
        result.response=response.get("text")
        return result

def main(args=None):
    rclpy.init(args=args)

    talk_action_server = AskActionServer()

    rclpy.spin(talk_action_server)


if __name__ == '__main__':
    main()

