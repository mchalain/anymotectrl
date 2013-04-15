#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <linux/input.h>

#ifdef REMOTEKEY
# include "remotekey.h"
#else
# include "kbdmapping.h"
#endif

int main(int argc, char **argv)
{
	int fd = -1;
	if (argc > 1)
	{
		fd = open(argv[1], O_WRONLY | O_CREAT, 0666);

		if (fd < 0)
			fprintf(stderr, "error on open file %d %s\n", errno, strerror(errno));
	}
	else
	{
		fd = 1;
	}
	if (fd > 0)
	{
#ifdef REMOTEKEY
		write(fd, (char *)keyremote, sizeof(keyremote));
#else
		write(fd, ascii_keyboard, sizeof(ascii_keyboard));
#endif
		close(fd);
	}
	return 0;
}
