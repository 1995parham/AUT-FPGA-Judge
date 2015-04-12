/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Sun 12 Apr 2015 10:07:29 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef TCP_H
#define TCP_H

void tcp_connect(const char *ip);

void tcp_tcp(void);

void tcp_recv_move(char *move, int size);

void tcp_send_move(const char *move);

#endif
