// In The Name Of God
// ========================================
// * File Name : common.h
// 
// * Creation Date : 05-12-2014
//
// * Last Modified : Sat 06 Dec 2014 11:41:25 PM IRST
//
// * Created By : Parham Alvani (parham.alvani@gmail.com)
// =======================================
#ifndef COMMON_H
#define COMMON_H

#include <sys/select.h>

#define MAX_BUFF 1000 * 1000

void die(const char *fmt, ...);

int timeval_subtract(const struct timeval *a, const struct timeval *b);	// return a - b in milliseconds   
#endif
