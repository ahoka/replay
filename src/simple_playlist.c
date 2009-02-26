#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "simple_playlist.h"

playlist
playlist_init(void)
{
	playlist p;

	p.tail = NULL;
	p.head = NULL;
	p.path = NULL;

	return p;
}

playlist *
playlist_push(playlist *prevnode, char *path)
{
	playlist *p;

	if (!path)
		return prevnode;

	p = (playlist *)malloc(sizeof(playlist));

	p->head = prevnode;
	p->path = strdup(path);
	p->tail = NULL;

	if (prevnode != NULL) {
		prevnode->tail = p;
	}

	return p;
}

char *
playlist_pop(playlist *lastnode)
{
	playlist *p;
	p = lastnode;
	char *track;

	if (p != NULL) {
		while (p->head != NULL) {
			p = p->head;
		}
		track = p->path;
		if (p->tail != NULL) {
			p->tail->head = NULL;
			free(p);
		}
		return track;
	}
	return NULL;
}
