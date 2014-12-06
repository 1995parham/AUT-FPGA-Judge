// In The Name Of God
// ========================================
// * File Name : serial.c
// 
// * Creation Date : 03-12-2014
//
// * Last Modified : Sat 06 Dec 2014 11:51:39 PM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>

#include "serial.h"
#include "common.h"

static const char* serial_dev[2] = {"/dev/ttyS0", "/dev/ttyS1"};
static struct termios oldtio[2], tio[2];
char team_ids[2][3] = {"01", "02"};

void init_serial(){
	int p;
	int ports = 1;

	const char init_code[2] = "0";
	char team_id[4];

	int temp_timeout;

	if (on_serial == 0) return;
	if (on_serial == 1) ports = 1;
	if (on_serial == 2) ports = 2;
  
	for (p = 0; p < ports; p++){
      		serial_fd[p] = open(serial_dev[p], O_RDWR | O_NOCTTY | O_NDELAY);
      		if(serial_fd[p] < 0 ){
			die("open_port: Unable to open /dev/ttyS%d - ", p);
      		}
   		// Set serial port options 
      		tcgetattr(serial_fd[p], &oldtio[p]); // Backup port settings
      		tcflush(serial_fd[p], TCIOFLUSH);
  
      		memset(&tio[p], 0, sizeof(tio[p]));
      		cfsetispeed(&tio[p], B115200);
      		cfsetospeed(&tio[p], B115200);
      		tio[p].c_cflag |= CS8;	// 8 data bits
      		tio[p].c_cflag |= CLOCAL;	// local connection, no modem control
      		tio[p].c_cflag |= CREAD;	// Enable reciever

      		tcsetattr(serial_fd[p], TCSANOW, &tio[p]);
      		tcflush(serial_fd[p], TCIOFLUSH);
		
		// flush 
		write(serial_fd[p], init_code, strlen(init_code));
	
		// at least 30s timeout for game initialization
		temp_timeout = move_timeout;
		if(move_timeout < 30) move_timeout = 30;
	
		if(read_all(serial_fd[p], 3, &team_id[p]) != 3){
			die("Timeout while waiting team code on serial port %d!\n", p);
		}
		printf("Team code on erial %d: %s\n", p, &team_id[p]);
		move_timeout = temp_timeout; // restore
	}
}

int read_all(int fd, int len, char* buffer){

	int got = 0;
	struct timeval start, timelimit, stop;
	fd_set read_fds, write_fds, except_fds; 
	
	FD_ZERO(&write_fds);
	FD_ZERO(&except_fds);

	gettimeofday(&start, NULL);
	timelimit = start;
	timelimit.tv_sec = timelimit.tv_sec + move_timeout;

	do{
		struct timeval now, timeout;
		int timeout_ms;

		gettimeofday(&now, NULL);
		timeout_ms = timeval_subtract(&timelimit, &now);
		if (timeout_ms <= 0)
			break; // no remaining time
		
		#ifdef DEBUG
     			fprintf(stderr, "remaining time: %d\n", timeout_ms);
		#endif
 
		timeout.tv_sec = timeout_ms / 1000;
		timeout.tv_usec = (timeout_ms % 1000) * 1000;
 
		FD_ZERO(&read_fds);
		FD_SET(fd, &read_fds);
		if(select(fd + 1, &read_fds, &write_fds, &except_fds, &timeout) == 1){
			read(fd, &buffer[got], 1);
		}else{
			printf("timeout!\n");
	       		got = 0;
	       		break; // timeout
	     	}
 
		if(buffer[got] != 0x0d && buffer[got] != 0x0a)	// Ignore LF and CR
			got++;
		
	}while(got < len);

	gettimeofday(&stop, NULL);
		
	#ifdef DEBUG
   		fprintf(stderr, "read %d bytes in %d msec.\n", got, timeval_subtract(&stop, &start));
	#endif
	return got;
}
