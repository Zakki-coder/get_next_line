#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>

int main(int argc, char **argv)
{
	char *line = NULL;
	int fd;

	printf("%d\n", argc);
	if (argc == 1)
	{
		printf("For one line\n");
		get_next_line(0, &line);
		printf("%s", line);
		printf("For two lines\n");
		get_next_line(0, &line);
		printf("%s", line);
		get_next_line(fd, &line);
		printf("%s", line);
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		printf("For one line\n");
		get_next_line(fd, &line);
		printf("%s", line);
		printf("For two lines\n");
		get_next_line(fd, &line);
		printf("%s", line);
		get_next_line(fd, &line);
		printf("%s", line);
	}
	return 0;
}
