#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	char *line = NULL;
	int fd;
	int ret = 1;

	printf("%d\n", get_next_line(42, &line));
	free (line);
	if (argc == 1)
	{
		while (ret)
		{
			ret = get_next_line(0, &line);
			printf("%s\n", line);
		}
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		while (ret)
		{
			ret = get_next_line(fd, &line);
		//	printf("%d\n", ret);
			printf("%s\n", line);
			free (line);
		}
		close (fd);
	}
	return 0;
}
