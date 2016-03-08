#Stabilize servo continuously
import sys, getopt
from Adafruit_PWM_Servo_Driver import PWM
import os
sys.path.append('.')
import RTIMU
import time
import numpy
import math
import string

#Setup for the Servos
pwm = PWM(0x40)
# Note if you'd like more debug output you can instead run:
#pwm = PWM(0x40, debug=True)

servoMin = 150 # Min pulse length out of 4096
servoMax = 600 # Max pulse length out of 4096
servoCenter = 375

def setServoPulse(channel, pulse):
  pulseLength = 1000000                   # 1,000,000 us per second
  pulseLength /= 60                       # 60 Hz
  print "%d us per period" % pulseLength
  pulseLength /= 4096                     # 12 bits of resolution
  print "%d us per bit" % pulseLength
  pulse *= 1000
  pulse /= pulseLength
  pwm.setPWM(channel, 0, pulse)

pwm.setPWMFreq(60)          # Set frequency to 60 Hz

# Setup for the IMU
SETTINGS_FILE = "RTIMULib"

print("Using settings file " + SETTINGS_FILE + ".ini")
if not os.path.exists(SETTINGS_FILE + ".ini"):
  print("Settings file does not exist, will be created")

s = RTIMU.Settings(SETTINGS_FILE)
imu = RTIMU.RTIMU(s)

print("IMU Name: " + imu.IMUName())

if (not imu.IMUInit()):
    print("IMU Init Failed")
    sys.exit(1)
else:
    print("IMU Init Succeeded")

# this is a good time to set any fusion parameters

imu.setSlerpPower(0.02)
imu.setGyroEnable(True)
imu.setAccelEnable(True)
imu.setCompassEnable(True)

poll_interval = imu.IMUGetPollInterval()
print("Recommended Poll Interval: %dmS\n" % poll_interval)

fusionCal = numpy.zeros([3,100])

#os.chdir(os.getcwd() +  "/launchData")
file = open("calData.txt")
for line in file:
	d,e,f = line.strip().split()
	print d,e,f

a = float(d)
b = float(e)
c = float(f)

loopCount = 0 #Used to count loops during calibration
imageCount = 1

fusionNums = numpy.zeros([3])

while True:
  if imu.IMURead():
    loopCount += 1
    # x, y, z = imu.getFusionData()
    # print("%f %f %f" % (x,y,z))
    data = imu.getIMUData()
    fusionPose = data["fusionPose"]
    fusionNums[0] = math.degrees(fusionPose[0]) - a
    fusionNums[1] = math.degrees(fusionPose[1]) - b
    fusionNums[2] = math.degrees(fusionPose[2]) - c
    pos1 = int(fusionNums.item(1)*3) + servoCenter
    pos2 = int(fusionNums.item(0)*3) + servoCenter
    pwm.setPWM(4, 0, pos1)   
    pwm.setPWM(6, 0, pos2)
    print("roll: %f pitch: %f yaw: %f pos1: %i pos2 %i" % (fusionNums[0], 
		fusionNums[1], fusionNums[2], pos1, pos2))
    time.sleep(poll_interval*1.0/1000.0)

file.close()
