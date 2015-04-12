/*
 * In The Name Of God
 * ========================================
 * [] File Name : main.c
 *
 * [] Creation Date : 24-02-2015
 *
 * [] Last Modified : Sun 12 Apr 2015 11:02:46 PM IRDT
 *
 * [] Created By : Parham Alvani (parham.alvani@gmail.com)
 * =======================================
*/
#include <glib.h>

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"
#include "serial.h"
#include "tcp.h"
#include "game.h"

static gchar *ip;
static gchar *spath;
static gint player;


static GOptionEntry entries[] = {
	{ "serial-path", 's', 0, G_OPTION_ARG_FILENAME, &spath,
		"Serial device file path", "N" },
	{ "ip-address", 'i', 0, G_OPTION_ARG_STRING, &ip,
		"Trax game server ip address", "M" },
	{ "player", 'p', 0, G_OPTION_ARG_INT, &player,
		"Trax game player number", "N"},
	{ NULL }
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
	if (!ip || !spath || !player)
		udie("%s", g_option_context_get_help(context, TRUE, NULL));

	open_serial(spath);
	init_serial(player);

	tcp_connect(ip);

	play(player);
}
