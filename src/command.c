/*
 * In The Name Of God
 * ========================================
 * [] File Name : command.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 24 Feb 2015 10:29:42 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "common.h"
#include "serial.h"

/*
 * Commands in this program have the following foramt
 * VERB [1] [2] ...      len(VERB) <= 10
 * every VERB have handler in following format
 * void command_VERB([1], [2], [3], ..)
*/


void quit_command(void)
{
	exit(0);
}

void init_command(void)
{
	on_serial = 2;
	init_serial();
}

void command_dispatcher(const char *command)
{
	char verb[10];
	int len;

	len = sscanf(command, "%s", verb);
	if (len < 1)
		return;

	if (!strcmp(verb, "quit"))
		quit_command();
	else if (!strcmp(verb, "init"))
		init_command();
}


