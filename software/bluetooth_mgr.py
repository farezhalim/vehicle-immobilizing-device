import zmq
import os
import time
import filecmp

def main():
	context = zmq.Context()
	
	sub = context.socket(zmq.SUB)
	sub.connect('tcp://localhost:5556')
	sub.setsockopt(zmq.SUBSCRIBE, '')
	
	pub = conetxt.socket(zmq.PUB)
	pub.bind('tcp://localhost:5556')
	
	id = 0
	
	while True:
		address, context = sub.recv_multipart()
		
		if contents == "Immobilized"
			os.system("sudo systemctl start bluetooth")
			os.system("sudo systemctl start obexpush")
			os.system("~/Desktop/bluetooth_ctl_mgr.sh")
		
		if contents == "Detecting"
			os.system("sudo systemctl stop bluetooth")
			os.system("sudo systemctl stop obexpush")
		
		if contents == "Disabled"
			os.system("sudo systemctl stop bluetooth")
			os.system("sudo systemctl stop obexpush")
			
			bool recieveFile = false
			bool matchToFile = false
			
			while (not recieveFile) and (not matchToFile):
				recieveFile = os.path.isfile('/bluetooth/key.txt')
				matchToFile = filecmp.cmp('/bluetooth/good.txt','/key.txt')
			
			os.system("sudo rm /bluetooth/key.txt")
				
		
	sub.close()
	context.term()
