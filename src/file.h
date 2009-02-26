#ifndef FILE_H
#define FILE_H

size_t	file_getsize(const char*);
FILE	*file_open(const char *);
size_t	file_read(void *, size_t, FILE *);
int	file_close(FILE *);

#endif
