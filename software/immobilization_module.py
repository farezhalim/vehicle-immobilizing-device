import serial
import time
import binascii

##def readLine(port):
##	rv=""
##	while True:
##		ch = port.read()
##		rv += ch.decode('utf-8')
##		if ch =='\r' or ch=='':
##			return rv

port = serial.Serial("/dev/serial0", baudrate=9600,timeout=1.0)

while True:
        #port.write(str.encode("ATZ"))
        rcv = port.readline()
        #rcv = port.read(100)
        print("\r\r\nReceieved CAN Packet:%s" % str(rcv))
       # print("\r\r\nReceieved CAN Packet:%s" % str(rcv.decode(errors='replace')))
