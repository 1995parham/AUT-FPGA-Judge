/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 24 Feb 2015 10:34:43 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef SERIAL_H
#define SERIAL_H

extern int on_serial;
extern int serial_fd[2];
extern int move_timeout;

void init_serial(void);

/* Read len bytes from fd, but without CR and LF */
int read_all(int fd, int len, char *buff);

#endif
