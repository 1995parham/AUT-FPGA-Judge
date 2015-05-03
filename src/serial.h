/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef SERIAL_H
#define SERIAL_H

void open_serial(const char *dev);

void set_timeout(int timeout);

void init_serial(int serial_no);

/*
 * Read len bytes from serial, but without CR and LF
 * in Specified time interval
*/
int timed_readline(char *buffer);

int writeline(const char *buffer);

#endif
