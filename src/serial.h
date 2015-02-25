/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Wed 25 Feb 2015 09:11:22 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef SERIAL_H
#define SERIAL_H

extern int move_timeout;

void init_serial(void);

/* Read len bytes from fd, but without CR and LF */
int read_all(int fd, int len, char *buff);

#endif
