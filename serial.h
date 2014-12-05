// In The Name Of God
// ========================================
// * File Name : serial.h
// 
// * Creation Date : 03-12-2014
//
// * Last Modified : Thu 04 Dec 2014 06:44:30 AM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================
#ifndef SERIAL_H
#define SERIAL_H

void init_serial();
int read_all(int fd, int len, char* buff);	// Read len bytes from fd, but without CR and LF

#endif
