# In The Name Of God
# ========================================
# [] File Name : Serial.py
#
# [] Creation Date : 29-04-2015
#
# [] Created By : Parham Alvani (parham.alvani@gmail.com)
# =======================================
__author__ = 'Parham Alvani'

import serial

srl = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, parity=serial.PARITY_ODD, bytesize=serial.EIGHTBITS)
filename = input("Input File Name: ")
print(filename)
file = open(filename, 'r')
file.read(1)
char = file.read(1)
while not char.find('}'):
    srl.write(bytes(char, 'ASCII'))
    char = file.read(1)
