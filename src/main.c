/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 24 Feb 2015 10:30:22 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "command.h"

int main(int argc, char *argv[])
{
	printf("AUT-FPGA-Judge version 69, Copyright (C)");
	printf("2015 Parham Alvani(parham.alvani@gmail.com)\n");
	printf("AUT-FPGA-Judge comes with ABSOLUTELY NO WARRANTY;");
	printf("for details type `show w'.\n");
	printf("This is free software,");
	printf(" and you are welcome to redistribute it\n");
	printf("under certain conditions; type `show c' for details.\n");
	printf("\n");

	char command[MAX_BUFF];

	while (1) {
		printf("AUT-FPGA-Judge> ");
		fgets(command, MAX_BUFF, stdin);
		command[strlen(command) - 1] = '\0';

		command_dispatcher(command);
	}
}
