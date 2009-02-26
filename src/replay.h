#ifndef REPLAY_H
#define REPLAY_H

#include <stdint.h>

#define REPLAY_ERR 0
#define REPLAY_OK  1

int display_with_curses;

typedef uint8_t playmode_t;

#define PLAYLIST_SHUFFLE	0x1
#define PLAYLIST_REPEAT		0x2

typedef struct _track_info {
	char *artist;
	char *title;
	char *filename;
	size_t filesize;
} track_info;

#endif
