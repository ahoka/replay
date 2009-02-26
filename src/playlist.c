#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "util.h"
#include "playlist.h"

playlist_t *
playlist_new(void)
{
	playlist_t *p;

	if ((p = (playlist_t *)malloc(sizeof(playlist_t))) == NULL)
		return NULL;

	p->head = NULL;
	p->current = NULL;
	p->tail = NULL;

	return p;
}

/* XXX TODO */
#if 0
playlist_t *
playlist_open(const char *path)
{
	playlist_t *p;

	if ((p = (playlist_t *)malloc(sizeof(playlist_t))) == NULL)
		return NULL;

	if (path) {
		/* insert stuff here to open saved playlists */
		t->path = strdup(path);
	}

	return p;
}
#endif

/*
 * free all tracks and then the list itself
 */

int
playlist_destroy(playlist_t *p)
{
	track_t *curr, *tmp;

	if (p == NULL)
		return -1;

	curr = p->head;

	while (curr != NULL) {
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}

	/* sleep well */
	free(p);

	return 0;
}


/*
 * Add a track to the end of the playlist
 */

int
playlist_add(playlist_t *p, const char *path)
{

	track_t *t;

	if (p == NULL)
		return -1;

	if ((t = (track_t *)malloc(sizeof(track_t))) == NULL) {
		perror("playlist_add(): Can't allocate memory.");
		exit(EXIT_FAILURE);
	}
	t->path = strdup(path);
	t->next = NULL;
	t->prev = NULL;

	/* Setup first item if not present. */
	if (p->head == NULL) {
		assert(p->tail == NULL);
		p->current = t;
		p->head = t;
	} else {
		p->tail->next = t;
		t->prev = p->tail;
	}
	p->tail = t;

//	*pls = p;

	return 0;
}

track_t *
playlist_get_next(playlist_t *p)
{
	track_t *t;

	if (p == NULL) {
		return NULL;
	}

	t = p->current;

	if (p->current != NULL)
		p->current = p->current->next;

	return t;
}

track_t *
playlist_get_prev(playlist_t *p)
{
	track_t *t;

	if (p == NULL) {
		return NULL;
	}

	if (p->current != NULL) {
		t = p->current->prev;
		p->current = p->current->prev;
	} else
		return NULL;

	return t;
}

/* unimplemented */
playlist_t *
playlist_dup(playlist_t *p, unsigned int howto)
{
	return p;
}
