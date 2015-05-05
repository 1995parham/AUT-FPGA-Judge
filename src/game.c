/*
 * In The Name Of God
 * ========================================
 * [] File Name : game.c
 *
 * [] Creation Date : 03-03-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/

#include "common.h"
#include "serial.h"
#include "tcp.h"

void play(int player_no)
{
	if (player_no == 1) {
		while (1) {
			char move[1024];

			move[0] = '\n';
			timed_readline(move);

			ulog("Serial player move : %s", move);

			tcp_send_move(move);
			tcp_recv_move(move, 1024);

			writeline(move);

			ulog("TCP player move : %s", move);
		}
	} else {
		while (1) {
			char move[1024];

			tcp_recv_move(move, 1024);

			ulog("TCP player move : %s", move);

			writeline(move);
			move[0] = '\n';
			timed_readline(move);

			ulog("Serial player move : %s", move);

			tcp_send_move(move);
		}
	}
}
