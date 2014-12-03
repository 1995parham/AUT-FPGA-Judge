// In The Name Of God
// ========================================
// * File Name : serial.c
// 
// * Creation Date : 03-12-2014
//
// * Last Modified : Wed 03 Dec 2014 08:49:22 PM IRST
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

static const char* serial_dev[2] = {"/dev/cauU0", "/dev/cauU1"};
int serial_dev_fd[2];	// This array visible to others file, os after init_srial it is going to be usable.
static struct termios oldtio[2], tio[2];
int on_serial = 0;	// Before call init_serial you set it to the number of serial port is going to be used. 

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
      		serial_fd[p] = open(serial_dev[p], O_RDWR | O_NOCTTY);
      		if(serial_fd[p] < 0 ){
			perror("open serial failed! ");
			exit(-1);
      		}
    
      		tcgetattr(serial_fd[p], &oldtio[p]); // Backup port settings
      		tcflush(serial_fd[p], TCIOFLUSH);
  
      		memset(&tio[p], 0, sizeof(tio[p]));
      		cfsetispeed(&tio[p], B115200);
      		cfsetospeed(&tio[p], B115200);
      		tio[p].c_cflag |= CS8; // 8N1
      		tio[p].c_cflag |= CLOCAL; // local connection, no modem control
      		tio[p].c_cflag |= CREAD;

      		tcsetattr(serial_fd[p], TCSANOW, &tio[p]);
      		tcflush(serial_fd[p], TCIOFLUSH);
	}
	// flush 
	write(serial_fd[p], init_code, strlen(init_code));
	
	// at least 30s timeout for game initialization
	temp_timeout = move_timeout;
	if(move_timeout < 30) move_timeout = 30;
		if(read_all(serial_fd[p], 3, team_id) != 3){
			printf("Timeout while waiting team code on serial port %d!\n", p);
			exit(-1);
		}
	team_id[3] = 0;
	printf("Team code on serial %d: %s\n", p, &team_id[1]);
	strncpy(team_ids[ ((on_serial==2) ? 1 : p) ], &team_id[1], 2);
	move_timeout = temp_timeout; // restore
}
