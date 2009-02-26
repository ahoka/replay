#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "buffer.h"

#include "locking.h"

uint8_t *
buf_get_r(ring_t *ring)
{
	uint8_t *buf;

	buf = ring->buf[ring->r];
	ring->r = ++ring->r % ring->chunks;

	return buf;
}

uint8_t *
buf_get_w(ring_t *ring)
{
	uint8_t *buf;

	buf = ring->buf[ring->w];
	ring->w = ++ring->w % ring->chunks;

	return buf;
}

void
buf_read(ring_t *ring, uint8_t *dest)
{
	size_t count;
	uint8_t *src;

	replay_sem_p(&ring->sem_filled);

	src = buf_get_r(ring);	/* get the next chunk to read from */
	assert(src != NULL);	/* this should be already initalized now */
	memcpy(dest, src, ring->size);

	replay_sem_v(&ring->sem_empty);
}

void
buf_store(ring_t *ring, const uint8_t *src)
{
	uint8_t *dest;

	replay_sem_p(&ring->sem_empty);

	dest = buf_get_w(ring);	/* get the next chunk to write to */
	assert(dest != NULL);	/* this should be already initalized now */
	memcpy(dest, src, ring->size);

	replay_sem_v(&ring->sem_filled);
}

void
buf_destroy(ring_t *ring)
{
	size_t i;

	for(i = 0; i < ring->chunks; i++)
		free(ring->buf[i]);

	free(ring);
	ring = NULL;
}

void
buf_init(ring_t *ring)
{
	assert(ring != NULL);
	ring->buf = malloc(ring->size * sizeof(uint8_t));
	if (!ring->buf) {
		perror("Can't allocate buffer");
		exit(EXIT_FAILURE);
	}
	buf_reset(ring);
}

void
buf_reset(ring_t *ring)
{
	size_t i;

	for(i = 0; i < ring->chunks; i++) {
		ring->buf[i] = malloc(ring->size);
		if (ring->buf[i] == NULL) {
			perror("buf_reset()");
			exit(EXIT_FAILURE);
		}
	}
}
