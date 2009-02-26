#include "util.h"

int
humanize(char *dest, size_t destlen, int src)
{
	float result;

	if (src < 1024) {
		snprintf(dest, destlen, "%d Bytes", src);
	} else if (src < (1024 * 1024)) {
		result = (float)src / 1024;
		snprintf(dest, destlen, "%.2f Kib", result);
	} else if (src < (1024 * 1024 * 1024)) {
		result = (float)src / (1024 * 1024);
		snprintf(dest, destlen, "%.2f Mib", result);
	} else {
		result = (float)src / (1024 * 1024 * 1024);
		snprintf(dest, destlen, "%.2f Gib", result);
	}
	return 0;
}
