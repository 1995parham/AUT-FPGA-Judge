/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.c
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
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tcp.h"
#include "common.h"

static int fd;

void tcp_init(void)
{
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if (fd <= 0)
		sdie("socket()");
}

void tcp_connect(const char *ip, uint16_t port)
{
	tcp_init();

	struct sockaddr_in server_address;

	server_address.sin_family = AF_INET;
	server_address.sin_addr.s_addr = inet_addr(ip);
	server_address.sin_port = htons(port);

	printf("connecting to %s\n", ip);
	if (connect(fd, (struct sockaddr *) &server_address,
		sizeof(server_address)) < 0)
		sdie("connect()");

}

void tcp_recv_move(char *move, int size)
{
	TEST_FD();

	FILE *sck = fdopen(fd, "r+");

	fgets(move, size, sck);
}

void tcp_send_move(const char *move)
{
	TEST_FD();

	FILE *sck = fdopen(fd, "r+");

	fprintf(sck, "%s\n", move);
	fflush(sck);
}
