// In The Name Of God
// ========================================
// * File Name : main.c
// 
// * Creation Date : 06-12-2014
//
// * Last Modified : Sun 07 Dec 2014 12:00:40 AM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "command.h"

int main(int argc, char* argv[]){
	printf("Gnomovision version 69, Copyright (C) 2015 Parham Alvani(parham.alvani@gmail.com)\n");
	printf("Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\n");
	printf("This is free software, and you are welcome to redistribute it\n");
    	printf("under certain conditions; type `show c' for details.\n");
	printf("\n");

	char command[MAX_BUFF];
	while(true){
		printf("AUT-FPGA-Judge> ");	
		fgets(command, MAX_BUFF, stdin);
		command[strlen(command) - 1] = '\0';
		
		command_dispatcher(command);
	}
}
