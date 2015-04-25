/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Mon 13 Apr 2015 07:04:14 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#ifndef TCP_H
#define TCP_H

#include <stdint.h>

void tcp_connect(const char *ip, uint16_t port);

void tcp_tcp(void);

void tcp_recv_move(char *move, int size);

void tcp_send_move(const char *move);

#endif
