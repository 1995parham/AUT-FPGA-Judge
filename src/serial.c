/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Thu 16 Apr 2015 08:19:55 AM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

#include "serial.h"
#include "common.h"

static int move_timeout;
static int fd;

void open_serial(const char *dev)
{
	fd = open(dev, O_RDWR | O_NOCTTY | O_NDELAY);
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
	struct timeval start, timelimit, stop;
	fd_set read_fds, write_fds, except_fds;

	FD_ZERO(&write_fds);
	FD_ZERO(&except_fds);

	gettimeofday(&start, NULL);
	timelimit = start;
	timelimit.tv_sec = timelimit.tv_sec + move_timeout;

	do {
		struct timeval now, timeout;
		int timeout_ms;

		gettimeofday(&now, NULL);
		timeout_ms = timeval_subtract(&timelimit, &now);
		if (timeout_ms <= 0)
			break; /* no remaining time */

		ulog("remaining time: %d\n", timeout_ms);

		timeout.tv_sec = timeout_ms / 1000;
		timeout.tv_usec = (timeout_ms % 1000) * 1000;

		FD_ZERO(&read_fds);
		FD_SET(fd, &read_fds);
		if (select(fd + 1, &read_fds, &write_fds,
					&except_fds, &timeout) == 1) {
			read(fd, &buffer[got], 1);
			got++;
		} else {
			printf("timeout!\n");
			got = 0;
			/* timeout */
			break;
		}

	} while (buffer[got - 1] != 0x0a);

	gettimeofday(&stop, NULL);

	ulog("read %d bytes in %d msec\n",
			got, timeval_subtract(&stop, &start));

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
