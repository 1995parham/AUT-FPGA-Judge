/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
/*
 * Copyright (c) 2015 Parham Alvani.
*/
#include <glib.h>

#include <stdbool.h>
#include <stdlib.h>

#include "common.h"
#include "serial.h"
#include "tcp.h"
#include "game.h"

static gchar *ip;
static gchar *dev;
static guint16 port;
static gint player;


static GOptionEntry entries[] = {
	{"serial-path", 's', 0, G_OPTION_ARG_FILENAME, &dev,
		"Serial device file path",     "N"},
	{"ip-address",  'i', 0, G_OPTION_ARG_STRING,   &ip,
		"Trax game server ip address", "M"},
	{"player",      'p', 0, G_OPTION_ARG_INT,      &player,
		"Trax game player number",     "N"},
	{"port",        'n', 0, G_OPTION_ARG_INT,      &port,
		"Trax game port number",       "N"},
	{NULL}
};


int main(int argc, char *argv[])
{
	GError *error = NULL;
	GOptionContext *context;

	context = g_option_context_new("- AUT FPGA Judge");
	g_option_context_add_main_entries(context, entries, NULL);
	if (!g_option_context_parse(context, &argc, &argv, &error)) {
		g_print("option parsing failed: %s\n", error->message);
		exit(1);
	}
	if (!ip || !dev || !player)
		udie("Please enter IP, Serial device and Player\n%s",
			g_option_context_get_help(context, true, NULL));

	open_serial(dev);
	init_serial(player);

	tcp_connect(ip, port);

	play(player);
}
