#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/stat.h>

/* Get basic file information though OS calls */
size_t
file_getsize(const char* path)
{
	struct stat	sb;
	int		r;

	r = stat(path, &sb);
	if (r)
		return 0;
	else
		return (size_t)sb.st_size;
}

FILE *
file_open(const char *path)
{
	return fopen(path, "r");
}

size_t
file_read(void *buf, size_t bufsz, FILE *stream)
{
	size_t r;
	r = fread(buf, 1, bufsz, stream);

	if (r < bufsz && ferror(stream)) {
		fprintf(stderr, "Error reading file.\n");
	}
	if (r < bufsz && feof(stream)) {
		fprintf(stderr, "EOF\n");
	}
	return r;
}

int
file_close(FILE *stream)
{
	return fclose(stream);
}

/* Decide how to open and open stream */
/* NOT IMPLENTED */
#if 0
int
url_open(const char *path)
{
	url = extract_url(path); /* XXX implement :) */
	if (url) {
		file_open(path);
	} else {
		switch (url) {
		case "http":
			http_open(path);
		}
	}
	return 0;
}
#endif
