/*
 * In The Name Of God
 * ========================================
 * [] File Name : serial.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Wed 25 Feb 2015 09:19:17 AM IRST
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

int serial_fd;
int move_timeout;

static const char *serial_dev = "/dev/ttyS0";
static struct termios oldtio, tio;

void init_serial(void)
{
	const char init_code[2] = "0";
	char team_id[4];

	int temp_timeout;

	serial_fd = open(serial_dev, O_RDWR | O_NOCTTY | O_NDELAY);
	if (serial_fd <= 0)
		sdie("Unable to open %s - ", serial_dev);

	/* Set serial port options */
	tcgetattr(serial_fd, &oldtio); /* Backup port settings */
	tcflush(serial_fd, TCIOFLUSH);

	memset(&tio, 0, sizeof(tio));
	cfsetispeed(&tio, B115200);
	cfsetospeed(&tio, B115200);
	tio.c_cflag |= CS8;	/* 8 data bits */
	tio.c_cflag |= CLOCAL;	/* local connection, no modem control */
	tio.c_cflag |= CREAD;	/* Enable reciever */

	tcsetattr(serial_fd, TCSANOW, &tio);
	tcflush(serial_fd, TCIOFLUSH);

	/* flush */
	write(serial_fd, init_code, strlen(init_code));

	/* at least 30s timeout for game initialization */
	temp_timeout = move_timeout;
	if (move_timeout < 30)
		move_timeout = 30;

	if (read_all(serial_fd, 3, team_id) != 3)
		udie("Timeout while waiting on serial port %s\n", serial_dev);

	printf("Team code on serial %s: %s\n", serial_dev, team_id);
	move_timeout = temp_timeout; /* restore */
}

int timed_read(int fd, int len, char *buffer)
{
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

		#ifdef DEBUG
			fprintf(stderr, "remaining time: %d\n", timeout_ms);
		#endif

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

	#ifdef DEBUG
		fprintf(stderr, "read %d", got);
		printf(" bytes in %d msec.\n", timeval_subtract(&stop, &start));
	#endif

	return got;
}
