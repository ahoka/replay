#ifndef OUT_AO_H
#define OUT_AO_H

#include "plugin.h"

int	out_ao_init(plugin_obj *obj);
int	out_ao_play(plugin_obj *obj, void *, size_t);
int	out_ao_destroy(plugin_obj *obj);

#endif
