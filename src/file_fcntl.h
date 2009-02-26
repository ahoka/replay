#ifndef FILE_H
#define FILE_H

size_t	file_getsize(const char*);
int	file_open(const char *);
size_t	file_read(void *, size_t, int);
int	file_close(int);

#endif
