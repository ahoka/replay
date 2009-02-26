#ifndef PLUGIN_H
#define PLUGIN_H

#include <stdint.h>
#include "playlist.h" 		/* ohoh! */

/*
 * PLUGIN API 0.3.1
 */

#define REPLAY_PLUGINAPI 0x000031

/* PLUGIN API */

typedef struct _plugin_obj {
	int32_t	bits;
	int32_t	channels;
	int32_t	rate;
	void	*data;
} plugin_obj;

#define NEW_PLUGIN_OBJ(a) a = malloc(sizeof(plugin_obj))

typedef struct _outplugin {
	int	(*init)(plugin_obj *);
	int	(*play)(plugin_obj *, uint8_t *, size_t);
	int	(*destroy)(plugin_obj *);
	plugin_obj	*state;
} outplugin_t;

typedef struct _inplugin {
	int	(*init)(plugin_obj *);
	int	(*decode)(plugin_obj *, uint8_t *, size_t, uint8_t *, size_t);
	int	(*getinfo)(plugin_obj *, track_t *);
	int	(*destroy)(plugin_obj *);
	plugin_obj	*state;
} inplugin_t;


#endif
