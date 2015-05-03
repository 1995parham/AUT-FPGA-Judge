/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <sys/time.h>

#include "serial.h"
#include "common.h"

static int move_timeout;
static int fd;

static int timeval_subtract(struct timeval *a, struct timeval *b)
{
	/* return a-b in milliseconds */
	return (int) ((a->tv_usec - b->tv_usec) / 1000 +
	              (a->tv_sec - b->tv_sec) * 1000);
}

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

	struct termios old_tio, tio;
	const char *init_code;

	if (player_no == 1)
		init_code = "-W\n";
	else
		init_code = "-B\n";

	/* ** Set serial port options ** */

	/* Backup port settings */
	tcgetattr(fd, &old_tio);
	tcflush(fd, TCIOFLUSH);

	memset(&tio, 0, sizeof(tio));

	cfsetispeed(&tio, B115200);
	cfsetospeed(&tio, B115200);
	/* 8 data bits */
	tio.c_cflag |= CS8;
	/* local connection, no modem control */
	tio.c_cflag |= CLOCAL;
	/* enable receiver */
	tio.c_cflag |= CREAD;
	/* set odd parity */
	// tio.c_cflag |= PARODD;

	tcsetattr(fd, TCSANOW, &tio);
	tcflush(fd, TCIOFLUSH);

	/* flush */
	write(fd, init_code, strlen(init_code));

	/* at least 10s timeout for game initialization */
	if (move_timeout < 10)
		move_timeout = 10;
}

/* TODO improved serial timed readline */
int timed_readline(char *buffer)
{
	/*
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
		if (read(fd, &buffer[got], 1) > 0) {
			got++;
		} else {
			printf("timeout!\n");
			got = 0; */
	/* timeout */
	/* break;
}
} while (buffer[got - 1] != '\n');

buffer[got] = 0;

return got; */

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
		if (timeout_ms <= 0) break; // no remaining time
		printf("remaining time: %d\n", timeout_ms);

		timeout.tv_sec = timeout_ms / 1000;
		timeout.tv_usec = (timeout_ms % 1000) * 1000;

		FD_ZERO(&read_fds);
		FD_SET(fd, &read_fds);
		if (select(fd + 1, &read_fds, &write_fds, &except_fds,
			&timeout) == 1) {
			read(fd, &buffer[got], 1);
		} else {
			printf("timeout!\n");
			got = 0;
			break; // timeout
		}

	} while (buffer[got] != '\n');

	if (buffer[got] != 0x0d && buffer[got] != 0x0a) got++;
	gettimeofday(&stop, NULL);
	printf("read %d bytes in %d msec.\n", got,
		timeval_subtract(&stop, &start));
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
