#!/bin/sh

sleep 1m

cd /home/pi/Desktop
sudo ./uartComm &
cd /home/pi/Desktop
python3 bluetooth_mgr.py &
cd /home/pi/Desktop
python3 detection.py &
