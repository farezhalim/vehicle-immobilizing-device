import zmq
import os
import time

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
			os.system("./bluetooth")

		
		if contents == "Detecting"
			os.system("sudo systemctl stop bluetooth")
			os.system("sudo systemctl stop obexpush")
		
		if contents == "Disabled"
			os.system("sudo systemctl stop bluetooth")
			os.system("sudo systemctl stop obexpush")

		
	sub.close()
	context.term()
