import serial
import sys
import string

ser = serial.Serial('/dev/ttyAMA0', 9600)
while True :
	try:
		# Read data incoming on the serial line
		data = ser.read(4)
		print data
		filename = "log"
		myfile = open(filename, 'a+')
		myfile.write(data)
		myfile.close()
	except:
		print "Unexpected error:", sys.exc_info()
		sys.exit()