import serial, sys
import os, random
import subprocess
from subprocess import call
import threading


ser = serial.Serial('/dev/cu.usbserial-AC01RUCV', 9600)

if (ser):
    print("Serial port " + ser.portstr + " opened.")

audio_files = []
for root, dirs, files in os.walk("./music", topdown=False):
    for name in files:
        if name.endswith('.mp3'):
            audio_files.append(os.path.join(root, name))

def player():
    pygame.init()
    pygame.mixer.init()
    pygame.mixer.music.load(file)
    pygame.mixer.music.play()
    while pygame.mixer.music.get_busy(): 
        pygame.time.Clock().tick(10)

while True:
    input_ = str(ser.read())
    print(input_)
    if not input_ == '' or not input_ == None:
        if input_ == "b'P'":
            # subprocess.call(["ffplay", "-nodisp", "-autoexit", "/music"])
            # random_file = str(random.sample(audio_files, 1)[0])
            # print(random_file)
            
            os.system(' osascript -e "set Volume 3"')
            # subprocess.call(["afplay", random_file], shell=False)
            # continue
            play_music = True

        elif input_ == "b'S'":
            play_music = False
            os.system(' osascript -e "set Volume 0"')
        
        elif input_ == "b'Q'":
            os.system(' poweroff')
