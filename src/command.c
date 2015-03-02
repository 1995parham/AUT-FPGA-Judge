/*
 * In The Name Of God
 * ========================================
 * [] File Name : command.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 12:01:24 AM IRST
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

void open_command(const char *dev)
{
	open_serial(dev);
}

void init_command(void)
{
	init_serial();
}

void command_dispatcher(const char *command)
{
	char verb[10];
	int len;

	len = sscanf(command, "%s", verb);
	if (len < 1)
		return;

	if (!strcmp(verb, "quit")) {
		quit_command();
	} else if (!strcmp(verb, "open")) {
		char dev[1024];
		int len = 0;

		len = sscanf(command, "%s %s", verb, dev);
		if (len < 2) {
			printf("open serial-device\n");
			return;
		}
		open_command(dev);
	} else if (!strcmp(verb, "init")) {
		init_command();
	}
}
