#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include <unistd.h>
#include <fcntl.h>
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

int
file_open(const char *path)
{
	return open(path, O_RDONLY, 0);
}

size_t
file_read(void *buf, size_t bufsz, int fd)
{
	size_t r;
	r = read(fd, buf, bufsz);

	if (!r)
		fprintf(stderr, "EOF\n");

	return r;
}

int
file_close(int fd)
{
	return close(fd);
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
