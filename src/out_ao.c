#include <assert.h>
#include <ao/ao.h>

#include "replay.h"
#include "plugin.h"
#include "util.h"

int
out_ao_init(plugin_obj *obj)
{
	ao_device		*dev;
	ao_sample_format	format;
	int			default_drv;

	NEW_PLUGIN_OBJ(obj);
	assert(obj != NULL);

	ao_initialize();

	default_drv = ao_default_driver_id();

	format.bits = obj->bits;
	format.channels = obj->channels;
	format.rate = obj->rate;
	format.byte_format = AO_FMT_LITTLE;

	dev = ao_open_live(default_drv, &format, NULL);
	if (dev == NULL)
		return REPLAY_ERR;

	obj->data = dev;

	assert(obj->data != NULL);
	return REPLAY_OK;
}

int
out_ao_play(plugin_obj *obj, void *buf, size_t bufsz)
{
	ao_play(obj->data, (char *)buf, bufsz);

	return REPLAY_OK;
}

int
out_ao_destroy(plugin_obj *obj)
{
	ao_close(obj->data);
	ao_shutdown();

	free(obj);

	return REPLAY_OK;
}
