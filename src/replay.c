#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <assert.h>

#include "replay.h"
#include "curses.h"
#include "plugin.h"
#include "playback.h"

#include "in_mp3.h"
#include "out_ao.h"

int	main(int, char**);
void	usage(void);
void	version(void);
void	display_help(void);
void	program_dies(int);

int
main(int argc, char **argv)
{
	extern char	*optarg;
	extern int	optind;
	int		rflag, ch, fd, ac;
	size_t		len;
	playlist_t	*playlist;

	display_with_curses = 0;

	signal(SIGINT, program_dies);
	signal(SIGTERM, program_dies);

	while ((ch = getopt(argc, argv, "vhrc")) != -1) {
		switch (ch) {
		case 'r':
			break;
		case 'c':
			display_with_curses = 1;
			break;
		case 'v':
			version();
			break;
		case 'h':
			display_help();
			break;
		case '?':
		default:
			usage();
		}
	}
	argc -= optind;
	argv += optind;

	/* hardcode this for now */
	outplugin_t out = {
		.init = out_ao_init,
		.play = out_ao_play,
		.destroy = out_ao_destroy
	};
	inplugin_t in = {
		.init = in_mp3_init,
		.decode = in_mp3_decode,
		.destroy = in_mp3_destroy
	};

	if (argc == 0) {
		fprintf(stderr, "Not enough arguments\n");
		return EXIT_FAILURE;
	}
	playlist = playlist_new();

	if (display_with_curses)
		curses_init();
	else
		printf("== Replay 0.3 ==\n");

	ac = argc;
	while (ac--) {
		playlist_add(playlist, *argv);
		argv++;
	}
	assert(playlist != NULL);

	playback(playlist, &out, &in, 0);

	if (display_with_curses)
		curses_destroy();

	printf("Good Bye!\n");

	return EXIT_SUCCESS;
}

void
program_dies(int msg)
{
	if (display_with_curses)
		curses_destroy();
	exit(EXIT_FAILURE);
}

void
usage(void)
{
	fprintf(stderr, "Usage: replay [-h][-vrc] filename\n");
	exit(EXIT_FAILURE);
}

void
display_help(void)
{
	fprintf(stderr,
	    "Usage: replay [-v|rc] filename\n"
	    "\t-v\tdisplay version\n"
	    "\t-r\trepeat playlist\n"
	    "\r-s\tshuffle playlist\n"
	    "\t-c\tuse curses interface\n"
	    "\t-h\tdisplay this help message\n");
	exit(EXIT_FAILURE);
}

void
version(void)
{
	fprintf(stderr, "replay - version 0.2 alpha\n");
	fprintf(stderr, "Copyright 2008, Adam Hoka\n");

	exit(EXIT_SUCCESS);
}
