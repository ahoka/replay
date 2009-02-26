#include <string.h>
#include <assert.h>

#include <mpg123.h>

#include "replay.h"
#include "plugin.h"
#include "util.h"
#include "playlist.h"

int
in_mp3_init(plugin_obj *obj)
{
	int	r;

	NEW_PLUGIN_OBJ(obj);

	assert(obj != NULL);

	if (mpg123_init() != MPG123_OK)
		return REPLAY_ERR;

	obj->data = mpg123_new(NULL, &r);
	if (obj->data == NULL)
		return REPLAY_ERR;

	if (mpg123_open_feed(obj->data) != MPG123_OK)
		return REPLAY_ERR;

	assert(obj->data != NULL);
	return REPLAY_OK;
}

#if 0
void *
in_mp3_open(char *file)
{
        mpg123_handle   *m;
        int             channels, encoding, r;
        long            rate;

        channels = encoding = 0;
        rate = 0;

        m = mpg123_new(NULL, &r);
        assert(m != NULL);
	/* verbosity */
        mpg123_param(m, MPG123_VERBOSE, 1, 0);
        r = mpg123_open(m, file);

	if (r != MPG123_OK)
		return NULL;
        assert(m != NULL);

        assert(mpg123_getformat(m, &rate, &channels, &encoding) == MPG123_OK);

        mpg123_format_none(m);
        mpg123_format(m, rate, channels, encoding);

        return m;
}

#endif

int
in_mp3_getinfo(void *m, track_t *track)
{
#if 0
	int		meta;
	mpg123_id3v2	*v2;
	mpg123_id3v1	*v1;

	v1 = NULL;
	v2 = NULL;

	/* move those to some global string db */
	info->artist = "Unknown Artist";
	info->title = "Unknown Title";

	mpg123_scan(m);
	meta = mpg123_meta_check(m);
	/* XXX - generalize this, toooooooo ugly */
	if ((meta & MPG123_ID3) && (mpg123_id3(m, &v1, &v2) == MPG123_OK)) {
		if (v1 != NULL) {
			info->artist = (char *)malloc(31);
			strncpy(info->artist, v1->artist, 30);

			if (info->artist[30]) {
				info->artist = realloc(info->artist, 31);
				assert(info->artist != NULL);
				info->artist[31] = '\0';
			}

			info->title = (char *)malloc(31);
			strncpy(info->title, v1->title, 30);

			if (info->title[30]) {
				info->title = realloc(info->title, 31);
				assert(info->title != NULL);
				info->title[31] = '\0';
			}
		}
		if (v2 != NULL) {
			if (v2->artist != NULL) {
				info->artist = (char *)malloc(v2->artist->size + 2);
				strncpy(info->artist, v2->artist->p, v2->artist->size);

				if (info->artist[v2->artist->size]) {
					info->artist[v2->artist->size + 1] = '\0';
				}
			}
			if (v2->title != NULL) {
				info->title = (char *)malloc(v2->title->size + 2);
				strncpy(info->title, v2->title->p, v2->title->size);

				if (info->title[v2->title->size]) {
					info->title[v2->title->size + 1] = '\0';
				}
			}
		}
	}
#endif
	return REPLAY_ERR;
}


int
in_mp3_destroy(plugin_obj *obj)
{
        mpg123_delete(obj->data);
        mpg123_exit();

	free(obj);
	obj = NULL;

	return REPLAY_OK;
}

size_t
in_mp3_decode(plugin_obj *obj, uint8_t *in, size_t insz, uint8_t *out, size_t *outsz)
{
        int		r;
        size_t		done;

	done = 0;
//	r = mpg123_decode((mpg123_handle *)obj->data, in, insz, out, outsz, &done);

	/* feed the decoder */
	r = mpg123_feed((mpg123_handle *)obj->data, in, insz);

	if (r != MPG123_DONE)
		abort(); 	/* LULZ TODO XXX WTF */

	/* read decoded data from internal buffer */
	r = mpg123_read((mpg123_handle *)obj->data, out, *outsz, &done);

	/* increase buffer space if we need more space */
	if (done > *outsz) {
		unsigned char	*tmp;
		int		newsz;

		newsz = done;
		tmp = malloc(newsz);
		memcpy(tmp, out, *outsz);

		r = mpg123_read((mpg123_handle *)obj->data, (tmp + *outsz), (newsz - *outsz), &done);
		assert(done == (newsz - *outsz));

		assert(out != NULL);
		free(out);
		out = tmp;

		*outsz = newsz;
	}

	if (r == MPG123_NEW_FORMAT) {
		long rate;
		int chan, enc;

		mpg123_getformat((mpg123_handle *)obj->data, &rate, &chan, &enc);

		obj->channels = chan; /* XXX */
		obj->rate = rate;

		/* TODO reinit output */
	}

#if 0
	while(ret != MPG123_ERR && ret != MPG123_NEED_MORE) {
		/* Get all decoded audio that is available now before feeding more input. */
		ret = mpg123_decode(m,NULL,0,out,OUTBUFF,&size);

	}
#endif

	if (r == MPG123_ERR)
		return 0;

        return done;
}
