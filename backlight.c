/* Very simple program to control the backlight brightness of a laptop
 *
 * Copyright (c) 2019  Joachim Nilsson <troglobit@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <dirent.h>
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLASS "/sys/class/backlight"
#define SCALE { 0, 0.1, 0.2, 0.3, 0.45, 0.6, 0.9, 1.2, 1.8, 2.7, 4, 6, 9, 13.5, 20, 30, 45, 67, 80, 100 }

/* From The Practice of Programming, by Kernighan and Pike */
#ifndef NELEMS
#define NELEMS(array) (sizeof(array) / sizeof(array[0]))
#endif

struct device {
	char *path;
	int max;
	int current;
};

extern char *__progname;


static int value(char *path, char *file, int val)
{
	size_t len;
	FILE *fp;
	char *fn, *mode;
	int rc;

	len = strlen(path) + strlen(file) + 2;
	fn = alloca(len);
	snprintf(fn, len, "%s/%s", path, file);

	if (val == -1)
		mode = "r";
	else
		mode = "w";

	fp = fopen(fn, mode);
	if (!fp)
		return -1;

	if (val == -1)
		rc = fscanf(fp, "%d", &val);
	else
		rc = fprintf(fp, "%d\n", val);
	if (!rc)
		warn("Failed %s value from %s", val == -1 ? "reading" : "writing", fn);

	fclose(fp);

	return val;
}

static void set(char *path, char *file, int val)
{
	int rc;

	rc = value(path, file, val);
	if (rc == -1)
		err(1, "Failed setting brightness");
}

static int get(char *path, char *file)
{
	return value(path, file, -1);
}
	
static int locate(struct device *dev)
{
	struct dirent *d;
	size_t len;
	DIR *dir;
	int found = 0;

	dir = opendir(CLASS);
	if (!dir)
		return 0;

	while ((d = readdir(dir))) {
		if (d->d_name[0] == '.')
			continue;

		len = strlen(CLASS) + strlen(d->d_name) + 2;
		dev->path = malloc(len);
		if (!dev->path)
			return 0;

		snprintf(dev->path, len, "%s/%s", CLASS, d->d_name);
		dev->max = get(dev->path, "max_brightness");
		dev->current = get(dev->path, "brightness");
		found = 1;
		break;
	}
	closedir(dir);

	return found;
}

static int best(int left, int right, int target)
{
	if (target - left >= right - target) 
		return right; 

        return left;
}

static int closest(int target, int values[], size_t num)
{
	int i = 0, j = num, mid = 0;

	if (target <= values[0])
		return values[0];
	if (target >= values[num - 1])
		return values[num - 1];

	while (i < j) {
		mid = (i + j) / 2;

		if (values[mid] == target)
			return values[mid];

		if (target < values[mid]) {
			if (mid > 0 && target > values[mid - 1])
				return best(values[mid - 1], values[mid], target);

			j = mid;
		} else {
			if (mid < num - 1 && target < values[mid + 1])
				return best(values[mid], values[mid + 1], target);
			i = mid + 1;
		}
	}

	return values[mid];
}

static void adjust(struct device *dev, int updown)
{
	float scale[] = SCALE;
	int values[NELEMS(scale)];
	int val, i;

	for (i = 0; i < NELEMS(scale); i++)
		values[i] = (int)(dev->max * scale[i] / 100);

	val = closest(dev->current, values, NELEMS(scale));
	for (i = 0; i < NELEMS(scale); i++) {
		if (values[i] == val)
			break;
	}

	i += updown;
	if (i >= NELEMS(scale) || i < 0)
		return;

	set(dev->path, "brightness", values[i]);
}

static void usage(void)
{
	printf("Usage: %s [command]\n"
	       "\n"
	       " up    Increase brightness\n"
	       " down  Decrease brightness\n"
	       "\n"
	       "Bug report address: https://github.com/troglobit/backlight/issues\n",
		__progname);
}

int main(int argc, char *argv[])
{
	struct device dev;

	if (!locate(&dev))
		err(1, "System has no backlight control");

	if (argc < 2) {
		printf("Found %s, max: %d, current: %d\n",
		       dev.path, dev.max, dev.current);
		return 0;
	}

	if (!strcasecmp(argv[1], "up"))
		adjust(&dev, +1);
	else if (!strcasecmp(argv[1], "down"))
		adjust(&dev, -1);
	else
		usage();

	return 0;
}
