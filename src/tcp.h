/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Tue 03 Mar 2015 10:35:09 AM IRST
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef TCP_H
#define TCP_H

void connect_tcp(const char *ip);

void init_tcp(void);

void recv_move(char *move, int size);

void send_move(const char *move);

#endif
