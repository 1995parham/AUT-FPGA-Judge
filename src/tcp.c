/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 12:31:58 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "tcp.h"

static int fd;

void recv_move(char *move, int size)
{
	FILE *sck  = fdopen(fd, "r+");

	fgets(move, size, sck);
}

void send_move(const char *move)
{
	FILE *sck = fdopen(fd, "r+");

	fprintf(sck, "%s\n", move);
	fflush(sck);
}
