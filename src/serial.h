// In The Name Of God
// ========================================
// * File Name : serial.h
// 
// * Creation Date : 03-12-2014
//
// * Last Modified : Tue 16 Dec 2014 01:04:49 PM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================
#ifndef SERIAL_H
#define SERIAL_H

extern int on_serial;
extern int serial_fd[2];
extern int move_timeout;

void init_serial();
int read_all(int fd, int len, char* buff);	// Read len bytes from fd, but without CR and LF

#endif
