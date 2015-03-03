/*
 * In The Name Of God
 * ========================================
 * [] File Name : game.c
 *
 * [] Creation Date : 03-03-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 11:53:56 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "serial.h"
#include "tcp.h"

void play(void)
{
	char move[1024];
	recv_move(move, 1024);
	
	ulog("%s", move);

	timed_readline(move);

	send_move(move);
}
