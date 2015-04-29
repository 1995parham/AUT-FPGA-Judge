/*
 * In The Name Of God
 * ========================================
 * [] File Name : game.c
 *
 * [] Creation Date : 03-03-2015
 *
 * [] Last Modified : Sun 12 Apr 2015 10:42:48 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "serial.h"
#include "tcp.h"

void play(int player_no)
{
	if (player_no == 1) {
		while (1) {
			char move[1024];

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
			timed_readline(move);

			ulog("Serial player move : %s", move);

			tcp_send_move(move);
		}
	}
}
