import zmq
import Adafruit_ADXL345
import RPi.GPIO as GPIO
import smbus
import csv
import time

#Definitions
_ADXL345_DEFAULT_ADDRESS = 0x53 # Assumes ALT address pin low
# Conversion factors
_ADXL345_MG2G_MULTIPLIER = 0.004 # 4mg per lsb
_STANDARD_GRAVITY = 9.80665 # earth standard gravity

_REG_DEVID               = 0x00 # Device ID
_REG_THRESH_TAP          = 0x1D # Tap threshold
_REG_OFSX                = 0x1E # X-axis offset
_REG_OFSY                = 0x1F # Y-axis offset
_REG_OFSZ                = 0x20 # Z-axis offset
_REG_DUR                 = 0x21 # Tap duration
_REG_LATENT              = 0x22 # Tap latency
_REG_WINDOW              = 0x23 # Tap window
_REG_THRESH_ACT          = 0x24 # Activity threshold
_REG_THRESH_INACT        = 0x25 # Inactivity threshold
_REG_TIME_INACT          = 0x26 # Inactivity time
_REG_ACT_INACT_CTL       = 0x27 # Axis enable control for [in]activity detection
_REG_THRESH_FF           = 0x28 # Free-fall threshold
_REG_TIME_FF             = 0x29 # Free-fall time
_REG_TAP_AXES            = 0x2A # Axis control for single/double tap
_REG_ACT_TAP_STATUS      = 0x2B # Source for single/double tap
_REG_BW_RATE             = 0x2C # Data rate and power mode control
_REG_POWER_CTL           = 0x2D # Power-saving features control
_REG_INT_ENABLE          = 0x2E # Interrupt enable control
_REG_INT_MAP             = 0x2F # Interrupt mapping control
_REG_INT_SOURCE          = 0x30 # Source of interrupts
_REG_DATA_FORMAT         = 0x31 # Data format control
_REG_DATAX0              = 0x32 # X-axis data 0
_REG_DATAX1              = 0x33 # X-axis data 1
_REG_DATAY0              = 0x34 # Y-axis data 0
_REG_DATAY1              = 0x35 # Y-axis data 1
_REG_DATAZ0              = 0x36 # Z-axis data 0
_REG_DATAZ1              = 0x37 # Z-axis data 1
_REG_FIFO_CTL            = 0x38 # FIFO control
_REG_FIFO_STATUS         = 0x39 # FIFO status
_INT_SINGLE_TAP          = 0b01000000 # SINGLE_TAP bit
_INT_DOUBLE_TAP          = 0b00100000 # DOUBLE_TAP bit
_INT_ACT                 = 0b00010000 # ACT bit
_INT_INACT               = 0b00001000 # INACT bit
_INT_FREE_FALL           = 0b00000100 # FREE_FALL  bit

class DataRate: #pylint: disable=too-few-public-methods
	RATE_3200_HZ    = 0b1111 # 1600Hz Bandwidth   140mA IDD
	RATE_1600_HZ    = 0b1110 #  800Hz Bandwidth    90mA IDD
	RATE_800_HZ     = 0b1101 #  400Hz Bandwidth   140mA IDD
	RATE_400_HZ     = 0b1100 #  200Hz Bandwidth   140mA IDD
	RATE_200_HZ     = 0b1011 #  100Hz Bandwidth   140mA IDD
	RATE_100_HZ     = 0b1010 #   50Hz Bandwidth   140mA IDD
	RATE_50_HZ      = 0b1001 #   25Hz Bandwidth    90mA IDD
	RATE_25_HZ      = 0b1000 # 12.5Hz Bandwidth    60mA IDD
	RATE_12_5_HZ    = 0b0111 # 6.25Hz Bandwidth    50mA IDD
	RATE_6_25HZ     = 0b0110 # 3.13Hz Bandwidth    45mA IDD
	RATE_3_13_HZ    = 0b0101 # 1.56Hz Bandwidth    40mA IDD
	RATE_1_56_HZ    = 0b0100 # 0.78Hz Bandwidth    34mA IDD
	RATE_0_78_HZ    = 0b0011 # 0.39Hz Bandwidth    23mA IDD
	RATE_0_39_HZ    = 0b0010 # 0.20Hz Bandwidth    23mA IDD
	RATE_0_20_HZ    = 0b0001 # 0.10Hz Bandwidth    23mA IDD
	RATE_0_10_HZ    = 0b0000 # 0.05Hz Bandwidth    23mA IDD (default value)

class Range: #pylint: disable=too-few-public-methods
	RANGE_16_G  = 0b11   # +/- 16g
	RANGE_8_G   = 0b10   # +/- 8g
	RANGE_4_G   = 0b01   # +/- 4g
	RANGE_2_G   = 0b00   # +/- 2g (default value)

# Get I2C bus
bus = smbus.SMBus(1)

accel = Adafruit_ADXL345.ADXL345()

def data_rate(val):
	#Set Data Rate for Accelerometer
	bus.write_byte_data(_ADXL345_DEFAULT_ADDRESS,_REG_BW_RATE,val)
	data_rate_readBack = bus.read_byte_data(_ADXL345_DEFAULT_ADDRESS,_REG_BW_RATE)
	return data_rate_readBack
	
def data_range(val):
	#Set Data Range for Accelermeter
	bus.write_byte_data(_ADXL345_DEFAULT_ADDRESS,_REG_DATA_FORMAT,val)
	data_rate_readBack = bus.read_byte_data(_ADXL345_DEFAULT_ADDRESS,_REG_DATA_FORMAT)
	return data_rate_readBack

def detectAccident():
	#Query for acceleration values (ADXL Digital MEMS Accelerometer) + Find if accident has been detected
	xAxisList = [0]*50 #Only store X-axis values for the past 0.5 second
	yAxisList = [0]*50
	accident = False
	while True:
		x,y,z = accel.read()
		#Convert to G Values
		x = round(x*17.2*10**-3, 5)
		y = round(y*17.2*10**-3, 5)
		z = round(z*17.2*10**-3, 5)
		print('X={0} G, Y={1} G, Z={2} G'.format(x,y,z))
		
		xAxisList.pop(24)
		yAxisList.pop(24)
		xAxisList.insert(0,x) 
		yAxisList.insert(0,y)
		
		yDiff = yAxisList[24] -yAxisList[0]
		xDiff = xAxisList[24] -xAxisList[0]
		
		if yDiff > 2 or xDiff > 2: #Determine if accident has been detected
			print('Accident has been detected. RIP.')
			accident = True
			return accident
			break


data_rate(DataRate.RATE_100_HZ) #set sampling rate of accelerometer to  100 Hz
data_range(Range.RANGE_8_G) #set data range of accelerometer to 8G

#IPC Socket Communication Initialization
context = zmq.Context()
	
sub = context.socket(zmq.SUB)
sub.connect('tcp://127.0.0.1:5558') # 5557 to 5558
sub.setsockopt_string(zmq.SUBSCRIBE, '')
	
pub = context.socket(zmq.PUB)
pub.bind('tcp://127.0.0.1:5556')
	
id = 1	

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(5,GPIO.OUT)
GPIO.setup(6,GPIO.OUT)



while True:
	GPIO.output(5, GPIO.HIGH)
	GPIO.output(6, GPIO.LOW)
	m_accident = detectAccident()
	if m_accident == True:
		print("I'M Here boolean flag true")
		GPIO.output(6, GPIO.HIGH)
		GPIO.output(5, GPIO.LOW)
		pub.send_string("Immobilized")

	contents = sub.recv()
	if contents.decode("utf-8") == "Detecting":
		print('I not here')
		GPIO.output(5, GPIO.HIGH)
		GPIO.output(6, GPIO.LOW)

		m_accident = detectAccident()
		if m_accident == True:
			GPIO.output(6, GPIO.HIGH)
			GPIO.output(5, GPIO.LOW)
			pub.send_string("Immobilized")	

					
sub.close()
context.term()


	
print('Accident has been detected. RIP.')

	
