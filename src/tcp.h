/*
 * In The Name Of God
 * ========================================
 * [] File Name : tcp.h
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#ifndef TCP_H
#define TCP_H

#include <stdint.h>

void tcp_connect(const char *ip, uint16_t port);

void tcp_tcp(void);

void tcp_recv_move(char *move, int size);

void tcp_send_move(const char *move);

#endif
