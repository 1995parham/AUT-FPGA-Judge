/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Sat 18 Apr 2015 08:09:39 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "serial.h"
#include "common.h"

static int move_timeout;
static int fd;

void open_serial(const char *dev)
{
	fd = open(dev, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (fd <= 0)
		sdie("Unable to open %s - ", dev);
}

void set_timeout(int timeout)
{
	move_timeout = timeout;
}

void init_serial(int player_no)
{
	TEST_FD();

	struct termios oldtio, tio;
	const char *init_code;

	if (player_no == 1)
		init_code = "-W\n";
	else
		init_code = "-B\n";

	/* ** Set serial port options ** */

	/* Backup port settings */
	tcgetattr(fd, &oldtio);
	tcflush(fd, TCIOFLUSH);

	memset(&tio, 0, sizeof(tio));

	cfsetispeed(&tio, B115200);
	cfsetospeed(&tio, B115200);
	/* 8 data bits */
	tio.c_cflag |= CS8;
	/* local connection, no moden control */
	tio.c_cflag |= CLOCAL;
	/* enable reciever */
	tio.c_cflag |= CREAD;

	tcsetattr(fd, TCSANOW, &tio);
	tcflush(fd, TCIOFLUSH);

	/* flush */
	write(fd, init_code, strlen(init_code));

	/* at least 10s timeout for game initialization */
	if (move_timeout < 10)
		move_timeout = 10;
}

int timed_readline(char *buffer)
{
	TEST_FD();

	int got = 0;
	struct timeval timeout;
	fd_set read_fds, write_fds, except_fds;

	FD_ZERO(&write_fds);
	FD_ZERO(&except_fds);
	FD_ZERO(&read_fds);
	FD_SET(fd, &read_fds);

	timeout.tv_sec = 0;
	timeout.tv_usec = move_timeout * 1000;

	select(fd + 1, &read_fds, &write_fds,
		&except_fds, &timeout);

	do {
		if (read(fd, &buffer[got], 1)) {
			got++;
		} else {
			printf("timeout!\n");
			got = 0;
			/* timeout */
			break;
		}
	} while (buffer[got - 1] != '\n');

	buffer[got] = 0;

	return got;
}

int writeline(const char *buffer)
{
	TEST_FD();

	int put = 0;

	while (buffer[put] != 0x0a) {
		write(fd, &buffer[put], 1);
		put++;
	}
	return put;

}
