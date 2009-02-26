#ifndef PLAYLIST_H
#define PLAYLIST_H

/* should be able to contain extm3u/plsv2 information */
typedef struct _track {
	char		*path;
	struct _track	*prev;
	struct _track	*next;
} track_t;

typedef struct _playlist {
	track_t	*head;
	track_t	*tail;
	track_t	*current;
} playlist_t;


playlist_t	*playlist_new(void);
playlist_t	*playlist_open(const char *);
int		playlist_add(playlist_t *, const char *);
track_t		*playlist_get_next(playlist_t *);
track_t		*playlist_get_prev(playlist_t *);

#endif
