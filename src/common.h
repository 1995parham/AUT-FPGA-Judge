/*
 * In The Name Of God
 * ========================================
 * [] File Name : common.h
 *
 * [] Creation Date : 21-12-2014
 *
 * [] Last Modified : Tue 24 Feb 2015 10:32:18 PM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef COMMON_H
#define COMMON_H

#define MAX_BUFF (1000 * 1000)
#define MAX_CONN (1024)

void sdie(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));
void udie(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));
void ulog(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));
void slog(const char *fmt, ...)
	__attribute__((format(printf, 1, 2)));
int timeval_subtract(const struct timeval *a, const struct timeval *b);
#endif
