/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 12:01:03 AM IRST
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

void init_serial(void)
{
	TEST_FD();

	struct termios oldtio, tio;
	const char init_code[2] = "0";
	char team_id[255];

	int temp_timeout;

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

	/* at least 60s timeout for game initialization */
	temp_timeout = move_timeout;
	if (move_timeout < 60)
		move_timeout = 60;

	if (timed_read(3, team_id) != 3)
		udie("Timeout while waiting on serial port\n");

	printf("Team code on serial %d: %s\n", fd, team_id);
	move_timeout = temp_timeout; /* restore */
}

int timed_read(int len, char *buffer)
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
		} else {
			printf("timeout!\n");
			got = 0;
			/* timeout */
			break;
		}

		/* Ignore LF and CR */
		if (buffer[got] != 0x0d && buffer[got] != 0x0a)
			got++;

	} while (got < len);

	gettimeofday(&stop, NULL);

	ulog("read %d bytes in %d msec\n", got, timeval_subtract(&stop, &start));

	return got;
}
