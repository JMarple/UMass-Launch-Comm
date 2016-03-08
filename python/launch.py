import sys, getopt, os
from Adafruit_PWM_Servo_Driver import PWM
sys.path.append('.')
import RTIMU
import os.path
from time import sleep
import math
import picamera
import RPi.GPIO as GPIO
import numpy
import subprocess as sp
import signal


from Adafruit_BME280  import *

from Adafruit_ADS1x15 import ADS1x15
#####################################

#Setup of directory to save in
#This will move the folder titles "launchData" to a new test folder and create a new folder called launch Data

dir = os.getcwd()
num = 1
if os.path.exists(dir + "/launchData"):
	while os.path.exists(dir + "/test" + str(num)):
		num +=1
	newdir = "test" + str(num)
	os.rename("launchData",newdir)
os.makedirs(dir + "/launchData")
os.chdir(dir + "/launchData")

launchDir = os.getcwd()

print os.getcwd()


####################################
#Setup of picamera
camera = picamera.PiCamera()
camera.resolution = (640,480)
camera.shutter_speed = 4000

#Setup for the BME280 sensor
sensor = BME280(mode=BME280_OSAMPLE_8)

temp = sensor.read_temperature()

####################################
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

###################################
#Setup for the ADC
pga = 6144
sps = 8
adc = ADS1x15(ic=0x01)

####################################
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
#################################################################
#Setup of button 
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)

button = 14

GPIO.setup(button, GPIO.IN, pull_up_down = GPIO.PUD_UP)



################################################################
#Setup of variables 
loopCount = 0 #Used to count loops so pictures get taken every 10 seconds 
imageCount = 0# Used to count how many images have been taken 

loop_Time = time.time() #Time that is used during each loop and for the 10 minutes after landing
start_Time = time.time() # time that the raspberry pi turns on and the program starts
run_Time = time.time() - start_Time #  time since start time
alt_Cal = sensor.read_altitude() #used to set the starting altitude as ground level
alt_AGL = 0 #recorded altitude above ground level
launch_Mode = True #boolean for determining if the rocket should enter launch mode, initiated by a button/switch
launch_Threshold = 100 #Threshold at which payload knows it has been launched using altimeter
Apogee_Trig = False #boolean for if apogee has been detected
launched = False #Boolean for if launch has occured
alt_Count = 0 #Count how many loops record decreasing altitude
irradiance_Threshold = 0  # Threshold for determining if payload has been ejected from fairings
alt_Temp = 0 #variable that is the previous recorded altitude
servo_One = 6 #Pin used by the servo 1
servo_Two = 4#pin used by servo 2
fusionNums = numpy.zeros([3])
alt_Temp2 = 0
##############################################################
#Calibration sequence
fusionCal = numpy.zeros([3,100])
print fusionCal

while loopCount < 150:
 	 if imu.IMURead():
		data = imu.getIMUData()
   		fusionPose = data["fusionPose"]
	 	print("roll: %f pitch: %f yaw: %f" % (math.degrees(fusionPose[0]), 
		math.degrees(fusionPose[1]), math.degrees(fusionPose[2])))
		loopCount += 1
		time.sleep(poll_interval*1.0/1000.0)

loopCount = 0
while loopCount < 50:
 	 if imu.IMURead():
		data = imu.getIMUData()
   		fusionPose = data["fusionPose"]
		fusionCal [0,loopCount] = math.degrees(fusionPose[0])
		fusionCal [1,loopCount] = math.degrees(fusionPose[1])
		fusionCal [2,loopCount] = math.degrees(fusionPose[2])
	 	print("roll: %f pitch: %f yaw: %f" % (math.degrees(fusionPose[0]), 
		math.degrees(fusionPose[1]), math.degrees(fusionPose[2])))
		loopCount += 1
		time.sleep(poll_interval*1.0/1000.0)

fusionCalNums = numpy.zeros([3])
fusionCalNums = numpy.mean(fusionCal,1)*2
#fusionCalNums[1] = numpy.mean(fusionCal,0)
#fusionCalNums[2] = numpy.mean(fusionCal,0)

print fusionCal
print fusionCalNums

fusionNums = numpy.zeros([3])

pwm.setPWM(4, 0, servoMin + 50)
pwm.setPWM(6, 0, 250) 
time.sleep(2)
pwm.setPWM(4, 0, servoMax - 50)
time.sleep(2)
pwm.setPWM(4, 0, servoCenter)
pwm.setPWM(6, 0, servoCenter)
time.sleep(2)

file  = open("calData.txt","w")
file.write("%f %f %f" % (fusionCalNums.item(0) , fusionCalNums.item(1) ,fusionCalNums.item(2) ))
file.close()

################################################################
#Create a file for storing data within the new library
file = open("data.txt","w")
file.write("Altitude  Voltage   Temp   Pres   Humidity   Roll   Pitch   Yaw")


##############################################################
while True:

	print("alt_Cal: %f" , alt_Cal)

	input_state = GPIO.input(button)
	if input_state == False:
		print("button pressed")
		launch_Mode = True
		time.sleep(0.2)
	#print(camera.exposure_speed)	

	while launch_Mode == True:
		if launched == True:
			time.sleep(0.05)
		else :	
			time.sleep(1)
		
		#Have to read temp before alt for some stupid reason that I dont understand
		alt_Temp = alt_AGL
		temp = sensor.read_temperature()
		alt_AGL = sensor.read_altitude() - alt_Cal

		######## For testing. Comment out for launch
		alt_AGL = alt_Temp2
		
		##############

		irradiance = adc.readADCSingleEnded(0,pga,sps)

		print("Altitude: %f  alt_count: %6.3f Irradiance: %6.3f " % (alt_AGL, alt_Count,irradiance))	

		if (alt_AGL >= 500):
			launched = True
			camera.start_preview()

		if alt_Temp > alt_AGL:
			alt_Count += 1
		else:
			alt_Count = 0
			
		########## For testing purposes. Comment for launch
		alt_Temp2+= 50
		alt_Count  = alt_Temp2 / 100
		############


		if (launched == True and (alt_Count > 5 or adc.readADCSingleEnded(0,pga,sps) > 2)):
			
			############## For testing, comment out for launch. UNCOMMENT alt_AGL read below!!!!!
			alt_temp2 = 5280
			alt_AGL = alt_temp2
			################


			#Take an image one second after deployment
			#Begin sub process for camera stabilization
			print os.getcwd()
			time.sleep(5)
			extProc = sp.Popen(['python','../launchStabilizer.py'])
			sleep(1)
			camera.capture('pic' + str(imageCount) + "-" + str(alt_AGL) +  ".jpg")
			imageCount +=1
			os.kill(extProc.pid, signal.SIGSTOP)

			while(1):
				alt_AGL = alt_temp2
				alt_temp2 -= 400
				loop_Time = time.time()
				
				if  (alt_AGL <1000 and imageCount < 7 ):
					os.kill(extProc.pid, signal.SIGCONT)
					sleep(0.2)
					print("staibilizer activated and image taken")					
					camera.capture('pic' + str(imageCount) + "-" + str(alt_AGL) +  ".jpg")
					imageCount += 1
					os.kill(extProc.pid, signal.SIGSTOP)

				if imageCount < 6:
					if (alt_AGL/1000/(6-imageCount)) < 1:
						os.kill(extProc.pid, signal.SIGCONT)
						sleep(0.2)
						print("staibilizer activated and image taken")					
						camera.capture('pic' + str(imageCount) + "-" + str(alt_AGL) +  ".jpg")
						imageCount += 1
						os.kill(extProc.pid, signal.SIGSTOP)
				
				#f imu.IMURead():

				#Record data
				######################
				#uncomment alt_AGL below
				######################
    				data = imu.getIMUData()
    				fusionPose = data["fusionPose"]
    				temp = sensor.read_temperature()
    				humidity = sensor.read_humidity()
    				pressure = sensor.read_pressure()
    				#alt_AGL = sensor.read_altitude() - alt_Cal
    				irradiance = adc.readADCSingleEnded(0,pga,sps)
    				UV = adc.readADCSingleEnded(1,pga,sps)
				run_Time = time.time() - start_Time

				#Write data to a file
				file.write("%6f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f\n" % 
				(run_Time,alt_AGL,irradiance,UV,temp,pressure,humidity,math.degrees(fusionPose[0]),
				math.degrees(fusionPose[1]),math.degrees(fusionPose[2])))

				#print data to screen
    				print("runTime: %f altitude: %f irradiance: %f UV: %f temp: %f pres: %f humid: %f roll: %f pitch: %f yaw: %f" % 
				(run_Time,alt_AGL,irradiance,UV,temp,pressure,humidity,math.degrees(fusionPose[0]),
				math.degrees(fusionPose[1]),math.degrees(fusionPose[2])))

				#continues to stabilize camera until 1 second has elapsed
   				while (time.time() - loop_Time < 1):
					
					if imu.IMURead():
						data = imu.getIMUData()
    						fusionPose = data["fusionPose"]
    						fusionNums[0] = math.degrees(fusionPose[0]) - fusionCalNums.item(0)
    						fusionNums[1] = math.degrees(fusionPose[1]) - fusionCalNums.item(1)
  						fusionNums[2] = math.degrees(fusionPose[2]) - fusionCalNums.item(2)
						pos1 = int(fusionNums.item(0)*3) + servoCenter
						pos2 = int(fusionNums.item(1)*3) + servoCenter
						if abs(pos1 - servoCenter) > 90:
							pos1 = 90 + servoCenter
						if abs(pos2 - servoCenter) > 90:
							pos2 = 90 + servoCenter
						pwm.setPWM(servo_One, 0, pos1)
						pwm.setPWM(servo_Two, 0, pos2)

				if alt_AGL < 50:
					sp.Popen.terminate(extProc)
					loop_Time = time.time()# Time at which landing has occured
					file.write("Landing has Occured")
					print("Landing has Occured")
					time.sleep(10)
					
					camera.capture('pic' + str(imageCount) + "-" + str(alt_AGL) +  ".jpg")
					imageCount += 1
					while (1):
						sleep(30)
						#Record data
    						data = imu.getIMUData()
    						fusionPose = data["fusionPose"]
    						temp = sensor.read_temperature()
    						humidity = sensor.read_humidity()
    						pressure = sensor.read_pressure()
    						alt_AGL = sensor.read_altitude() - alt_Cal
    						irradiance = adc.readADCSingleEnded(0,pga,sps)
    						UV = adc.readADCSingleEnded(1,pga,sps)
						run_Time = time.time() - start_Time

						#Write data to a file
						file.write("%6f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f , %6.3f\n" % 
						(run_Time,alt_AGL,irradiance,UV,temp,pressure,humidity,math.degrees(fusionPose[0]),
						math.degrees(fusionPose[1]),math.degrees(fusionPose[2])))

						#print data to screen
		    				print("runTime: %f altitude: %f irradiance: %f UV: %f temp: %f pres: %f humid: %f roll: %f pitch: %f yaw: %f" % 
						(run_Time,alt_AGL,irradiance,UV,temp,pressure,humidity,math.degrees(fusionPose[0]),
						math.degrees(fusionPose[1]),math.degrees(fusionPose[2])))

						if time.time() > loop_Time + 6*1: #Change the 1 to 10 for launch
							camera.capture('pic' + str(imageCount) +  "-" + str(alt_AGL) + ".jpg")
							file.write("Mission Success")
							print("Mission Success")
							file.close()
							camera.stop_preview()
							exit()


file.close()
