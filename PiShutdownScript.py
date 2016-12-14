#!/bin/python  
# Configure Rpi to check if the GPIO pin for shutdown is high, if so, shutdown the Rpi.
  
import RPi.GPIO as GPIO  
import time  
import os  

int shutdownPin = 23

# Setup  shutdownPin with pull DOWN enabled.  
GPIO.setmode(GPIO.BCM)  
GPIO.setup(shutdownPin, GPIO.IN, pull_up_down = GPIO.PUD_DOWN)  
 
# Gracefully shutdown when shutdownPin is HIGH
def Shutdown(channel):  
    os.system("sudo shutdown -h now")  
 
# Detect when shutdownPin goes high, and run the shutdown function
GPIO.add_event_detect(23, GPIO.RISING, callback = Shutdown, bouncetime = 2000)  
 
# Sleep thread so that shutdownPin is only checked once a second 
while 1:  
    time.sleep(1)
