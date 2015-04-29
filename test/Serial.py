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

srl = serial.Serial(port='/dev/ptmx', baudrate=9600, parity=serial.PARITY_ODD, bytesize=serial.EIGHTBITS)
while True:
    command = input("> ")
    srl.write(bytes(command, "ASCII"))
