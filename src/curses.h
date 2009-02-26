#ifndef CURSES_H
#define CURSES_H

#include "playlist.h"

int curses_init(void);
void curses_destroy(void);
int curses_draw(track_t *);

#endif
