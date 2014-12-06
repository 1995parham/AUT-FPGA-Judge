#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "command.h"
#include "common.h"

// Commands in this program have the following foramt
// VERB [1] [2] ...      len(VERB) <= 10
// every VERB have handler in following format 
// void command_VERB([1], [2], [3], ..) 
//


void quit_command(){
	exit(0);
}

void command_dispatcher(const char* command){
	char verb[10];
	sscanf(command, "%s", verb);

	if(!strcmp(verb, "quit")){
		quit_command();
	}
}


