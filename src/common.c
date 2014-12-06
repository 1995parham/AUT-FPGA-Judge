// In The Name Of God
// ========================================
// * File Name : common.c
// 
// * Creation Date : 05-12-2014
//
// * Last Modified : Sat 06 Dec 2014 11:41:36 PM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "common.h"

void die(const char *fmt, ...){
	char buf[MAX_BUFF];
	
	va_list args; 
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);

	perror(buf);
	exit(EXIT_FAILURE);
}

int timeval_subtract(const struct timeval *a, const struct timeval *b){
	return (a->tv_usec - b->tv_usec) / 1000 + (a->tv_sec - b->tv_sec) * 1000;
}

