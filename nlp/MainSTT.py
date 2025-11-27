import queue, sys, sounddevice as sd
from vosk import Model, KaldiRecognizer

model = Model("../vosk-model-small-en-us-0.15")

q = queue.Queue()
def callback(indata, frames, time, status):
    if status: print(status, file=sys.stderr)
    q.put(bytes(indata))

samplerate = int(sd.query_devices(None, "input")["default_samplerate"])
rec = KaldiRecognizer(model, samplerate)

print("🎙️  Escuchando... (Ctrl+C para salir)\n")

with sd.RawInputStream(samplerate=samplerate, blocksize=4000, dtype="int16", channels=1, callback=callback):
    while True:
        data = q.get()
        if rec.AcceptWaveform(data):
            print(rec.Result())
