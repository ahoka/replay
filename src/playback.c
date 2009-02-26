#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/* is this portable? */
#include <libgen.h>

#include "replay.h"
#include "plugin.h"
#include "buffer.h"
/* XXX threads.h? */
#include "locking.h"
#include "playlist.h"
#include "curses.h"
#include "file.h"

/* new playback:

   init objects

   open file
   init in -> stats
   stats -> init out
   start read
   start write

   read thread:
    read file -> data
    data -> buffer store

   write thread:
    read buffer -> data
    data -> play

   close reader
   close writer

 */

int
playback(playlist_t *playlist, outplugin_t *out, inplugin_t *in, playmode_t playmode)
{
	track_t		*track;		/* track information */
	int		r, ret; 		/* result */
	size_t		d;		/* decode result */

	char		*filename;
	size_t		inbufsz, outbufsz;
	uint8_t		*inbuf, *outbuf;
	FILE		*stream;

	ret = out->init(out->state);
	if (ret == REPLAY_ERR) {
		fprintf(stderr, "Error: Can't init audio output.\n");
		exit(EXIT_FAILURE);
	}

	/* outer playlist item loop */
	while ((track = playlist_get_next(playlist)) != NULL) {
		printf("Opening file: %s\n", basename(track->path));
		printf("Filesize: %d bytes\n", file_getsize(track->path));
		stream = file_open(track->path);

		ret = in->init(in->state);
		if (ret == REPLAY_ERR)
			abort(); /* XXX */

		/* inner decoder loop */
		for(;;) {
			r = file_read(inbuf, inbufsz, stream);

			/* decode and play buffer content */
			d = in->decode(in->state, inbuf, r, outbuf, outbufsz);
			out->play(out->state, outbuf, d);

			/* zero bytes read, nothing to decode */
			if (r < inbufsz)
				break;

			/* zero the buffers for the next run (?) */
			memset(inbuf, 0, inbufsz);
			memset(outbuf, 0, outbufsz);
		}
		in->destroy(in->state);

		file_close(stream);
	}

	/* lets free the buffers */
	assert(inbuf != NULL);
	assert(outbuf != NULL);

	free(inbuf);
	free(outbuf);

	out->destroy(out->state);

        return 0;
}

/*
 * ring_t
 *   buffer[]
 *   sem_filled
 *   sem_empty
 */

#if 0
/* decoder thread */
void
playback_decode(ring_t *ring)
{
	uint8_t *inbuf, tmp;
	size_t	inbufsz, tmpsz;

	inbufsz = 512;
	inbuf = calloc(1, inbufsz * sizeof(uint8_t));

	tmpsz = 1024;
	tmpbuf = calloc(1, inbufsz * sizeof(uint8_t));

	for (;;) {
		file_read(inbuf, NULL, &inbufsz);

		in->decode(obj, inbuf, inbufsz, tmp, tmpsz);

		replay_sem_p(&ring->sem_filled);
		buf_store(ring, tmp);
		replay_sem_v(&ring->sem_empty);
	}
}

/* player thread */
void
playback_play(ring_t *ring)
{
	uint8_t *tmp;
	size_t	tmplen;

	for(;;) {
		replay_sem_p(&ring->sem_empty);
		buf_read(ring, tmp, tmplen);
		replay_sem_v(&ring->sem_filled);
		out_play(obj, tmp, tmplen);
	}
}
#endif
