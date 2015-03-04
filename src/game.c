/*
 * In The Name Of God
 * ========================================
 * [] File Name : game.c
 *
 * [] Creation Date : 03-03-2015
 *
 * [] Last Modified : Wed 04 Mar 2015 12:22:06 PM IRST
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
	while (1) {
		char move[1024];
		
		recv_move(move, 1024);

		ulog("TCP move : %s", move);

		timed_readline(move);

		ulog("Serial move : %s", move);
		
		send_move(move);
	}
}
