#include "config.h"

#include <stdlib.h>
#include <stdio.h>

#if defined(CURSES_HAVE_CURSES_H) && !defined(__NetBSD__)
# include <curses.h>
#elif defined(CURSES_HAVE_NCURSES_H)
# include <ncurses.h>
#else
# error "No curses header file. We are fucked."
#endif

#include "replay.h"
#include "util.h"

int screen_setup(void);

static const int offset = 1; 	/* offset to display text */

int
curses_init(void)
{
	WINDOW		*w;
	char	        *buf;
	size_t		bufsz;

#if 0
	if (LINES < 10 || COLS < 20) {
		fprintf(stderr, "Please make sure you have at least a terminal size of 10x20!\n");
		return EXIT_FAILURE;
	}
#endif

	w = initscr();
	if (!w) {
		perror("Can't initialize screen!");
		return EXIT_FAILURE;
	}

	cbreak();
	noecho();

	/* hide cursor */
	curs_set(0);

	/* XXX check for OK/ERR */

	if (has_colors) {
		start_color();
		use_default_colors();
	}

	return 0;
}

void
curses_destroy(void)
{
	endwin();
}

int
curses_draw(track_info *info)
{
	size_t		bufsz;
	char		*buf;
	char		tmpbuf[32]; /* used by humanize */

	bufsz = 81;
	buf = malloc(bufsz);

	clear();

	attrset(A_REVERSE | A_BOLD);
	mvaddstr(0, offset, ":: Replay 0.2 ::");
	attrset(A_NORMAL);
	humanize(tmpbuf, sizeof(tmpbuf), info->filesize);
	snprintf(buf, bufsz, "File: %s (%s)", info->filename, tmpbuf);
	mvaddstr(2, offset, buf);
	snprintf(buf, bufsz, "%s - %s", info->artist, info->title);
	mvaddstr(4, offset, buf);

	/* Go! Lightning strike! */
	refresh();

	free(buf);

	return 0;
}
