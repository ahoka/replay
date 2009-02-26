#ifndef IN_MP3_H
#define IN_MP3_H

#include "plugin.h"

int	in_mp3_init(plugin_obj *obj);
void	*in_mp3_open(char *);
int	in_mp3_decode(plugin_obj *obj, void *, size_t, void *, size_t);
int	in_mp3_destroy(plugin_obj *obj);
int	in_mp3_getinfo(void *, track_info *);

#endif
