// In The Name Of God
// ========================================
// * File Name : serial.h
// 
// * Creation Date : 03-12-2014
//
// * Last Modified : Sat 06 Dec 2014 11:52:00 PM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================
#ifndef SERIAL_H
#define SERIAL_H

int on_serial = 0;	// Before call init_serial you set it to the number of serial port is going to be used. 
int serial_fd[2];	// This array visible to others file, so after init_srial it is going to be usable.
int move_timeout = 1;

void init_serial();
int read_all(int fd, int len, char* buff);	// Read len bytes from fd, but without CR and LF

#endif
