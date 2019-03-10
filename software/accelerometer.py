# accelerometer.py
# simple program to sample the accelerometer axis data
# TODO: need to store in a 2D array
# TODO: save file
# TODO: detect a large spike

import time
import Adafruit_ADXL345
import datetime
import matplotlib.pyplot as plt
import numpy as np

# np.random.seed(444)

accelerometer = Adafruit_ADXL345.ADXL345()

accelerometer.set_range(Adafruit_ADXL345.ADXL345_RANGE_8_G) # set range to 8G
sampleRate = 50
accelerometer.set_rate() # set rate to 50 hz

delay = 0.02 # collects data per second
duration = 10 # seconds

#file = open("/home/pi/data_log.csv", "a")
#if os.stat("/home/pi//Desktop/data_log.csv").st_size == 0:
#	file.write("DateTime,X-axis,Y-axis,Z-axs=is\n")

## Don't run both loops
## permanent loop write to CSV file (CTRL-C to terminate)
with open("/home/pi/data.csv", "a") as log:
	while True:
		now = datetime.datetime.now()
		x, y, z = accelerometer.read()
		print('X={0}, Y={1}, Z={2}'.format(x,y,z))
		log.write("{0},{1},{2},{3}\n".format(str(now),str(x),str(y),str(z)))
		time.sleep(delay)

## loop that runs for a specific duration
for i in range(duration/delay):
	now = datetime.datetime.now()
    x, y, z = accelerometer.read()

    print('X={0}, Y={1}, Z={2}'.format(x,y,z))

    file.write(str(now)+","+str(x)+","+str(y)+","+str(z)+"\n")
    file.flush()

    time.sleep(delay)

file.close()
