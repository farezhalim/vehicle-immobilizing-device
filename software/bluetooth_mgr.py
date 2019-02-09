import zmq
import os
import time
import subprocess

def main():
    context = zmq.Context()

    sub = context.socket(zmq.SUB)
    sub.connect('tcp://localhost:5556')
    sub.setsockopt(zmq.SUBSCRIBE, '')

    pub = context.socket(zmq.PUB)
    pub.bind('tcp://localhost:5556')

    id = 0

    while True:
        address, contents = sub.recv_multipart()
        
        if contents == "Immobilized":
            os.system("systemctl start bluetooth")
            os.system("sudo hciconfig hci sspmode 0")
            os.system("sudo bt-agent -c NoInputNoOutput -p ~/Desktop/bluetooth.cfg")

            #if device connected, pub.send("message")
            os.system("hcitool con")
            out = check_output(['hcitool','con'])
            print out
            
        if contents == "Detecting":
            os.system("systemctl stop bluetooth")
            
        if contents == "Disabled":
            os.system("systemctl stop bluetooth")

    sub.close()
    context.term()
