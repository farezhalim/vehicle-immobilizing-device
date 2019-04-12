import zmq
import os
import time
import filecmp


#IPC Communication Initialization
context = zmq.Context()
	
sub = context.socket(zmq.SUB)
sub.connect('tcp://127.0.0.1:5557')
sub.setsockopt_string(zmq.SUBSCRIBE, '')
	
pub = context.socket(zmq.PUB)
pub.bind('tcp://127.0.0.1:5558')
	
id = 0
	
while True:
	contents = sub.recv()
	print(contents)
		
	if contents.decode("utf-8") == "EnableBT": #Start Bluetooth recption if vehicle is in an accident
		print("i am trying to enable bluetooth")
		os.system("sudo systemctl start bluetooth")
		os.system("sudo systemctl start obexpush")
		os.system("/home/pi/Desktop/bluetooth_ctl_mgr.sh") #Enable discoverable bluetooth flag
		recieveFile = False
		matchToFile = False
			
		while (not recieveFile): #Check whether key has been recieved
			#print("waiting for file")
			recieveFile = os.path.isfile('/bluetooth/key.txt')
			
		if recieveFile == True:
			print("file received, comparing...")
			
			time.sleep(5)
			matchToFile = filecmp.cmp('/bluetooth/good.txt','/bluetooth/key.txt', shallow=False)
			
			print(matchToFile)
			
			if matchToFile == True:
				print("file match!")
				os.system("sudo rm /bluetooth/key.txt")
				pub.send_string("Disabled")	
			else:	
				print("file did not match!")
		
	else:
		os.system("sudo systemctl stop bluetooth")
		os.system("sudo systemctl stop obexpush")
		
sub.close()
context.term()
