from espeak_ng import espeak_AUDIO_OUTPUT
import espeak_ng
import time

"""
Simple 'hello world' example.
"""

def main():
    text_to_synthesize = "Hello, Welcome, What is your name?"
    espeak_ng.initialize(output=espeak_AUDIO_OUTPUT.AUDIO_OUTPUT_SYNCH_PLAYBACK)
    espeak_ng.set_voice_by_properties(name="mb-us2")
    espeak_ng.synth(text_to_synthesize)


if __name__ == "__main__":
    main()
