/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 10:41:19 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>

#include "tcp.h"
#include "common.h"

static int fd;

void init_tcp(void)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd <= 0)
			sdie("socket()");


}

void connect_tcp(const char *ip)
{
	init_tcp();
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);
	server_addr.sin_port = htons(1373);
	
	if(connect(fd, (struct sockaddr *)&server_addr,
				sizeof(server_addr)) < 0)
		sdie("connect()");

}

void recv_move(char *move, int size)
{
	TEST_FD();

	FILE *sck  = fdopen(fd, "r+");

	fgets(move, size, sck);
}

void send_move(const char *move)
{
	TEST_FD();

	FILE *sck = fdopen(fd, "r+");

	fprintf(sck, "%s\n", move);
	fflush(sck);
}
