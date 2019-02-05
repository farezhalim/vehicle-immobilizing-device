# accelerometer.py
# simple program to sample the accelerometer axis data
# TODO: need to store in a 2D array
# TODO: save file
# TODO: detect a large spike 

import time
import Adafruit_ADXL345

accelerometer = Adafruit_ADXL345.ADXL345()

# set range to 8G
accelerometer.set_range(Adafruit_ADXL345.ADXL345_RANGE_8_G)
data = ["X", "Y", "Z"]

for i in range(20):
    x, y, z = accelerometer.read()
    print('X={0}, Y={1}, Z={2}'.format(x,y,z))

    data.append(x)
    data.append(y)
    data.append(z)
    
    time.sleep(0.5)

print(data)

