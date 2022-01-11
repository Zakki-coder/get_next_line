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

	if (get_next_line(42, &line) != -1)
		printf("ERROR should return -1 with fd 42");
	free (line);
	if (argc == 1)
	{
		while (ret)
		{
			ret = get_next_line(0, &line);
			printf("ret: %d\n", ret);
			printf("%s\n", line);
		}
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			printf("%s\n", line);
			printf("ret: %d\n", ret);
			free (line);
		}
		close (fd);
	}
	return 0;
}
