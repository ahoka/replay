#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>
#include "locking.h"

typedef struct _ring {
	uint8_t		**buf;		/* array of chunk structs */
	size_t		size;		/* size of stored data */
	size_t		chunks;		/* number of chunks */
	size_t		r;		/* read offset */
	size_t		w;		/* write offset */
	replay_sem	sem_filled;
	replay_sem	sem_empty;
} ring_t;

uint8_t	*buf_get_r(ring_t *ring);
uint8_t	*buf_get_w(ring_t *ring);
void	buf_read(ring_t *ring, uint8_t *dest);
void	buf_store(ring_t *ring, const uint8_t *src);
void	buf_destroy(ring_t *ring);
void	buf_init(ring_t *ring);
void	buf_reset(ring_t *ring);

#endif
