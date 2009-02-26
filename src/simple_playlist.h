#ifndef SIMPLE_PLAYLIST_H
#define SIMPLE_PLAYLIST_H

typedef struct Playlist {
	struct Playlist	*head;
	char		*path;
	struct Playlist	*tail;
} playlist;

playlist playlist_init();
playlist *playlist_push(playlist *, char *);
char *playlist_pop(playlist *);

#endif
