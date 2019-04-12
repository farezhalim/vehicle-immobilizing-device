import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(5,GPIO.OUT)
GPIO.output(5, GPIO.HIGH)
time.sleep(2)
GPIO.output(5, GPIO.LOW)
