/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 01:45:04 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef SERIAL_H
#define SERIAL_H

void open_serial(const char *dev);

void set_timeout(int timeout);

void init_serial(void);

/*
 * Read len bytes from serial, but without CR and LF
 * in Specified time interval
*/
int timed_readline(char *buffer);

#endif
