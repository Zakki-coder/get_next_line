#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *line = NULL;
	int fd;
//	int fd2;
	int ret = 1;

	if (get_next_line(42, &line) != -1)
		printf("ERROR should return -1 with fd 42");
	free (line);
	if (argc == 1)
		fd = 0;
	else
		fd = open(argv[1], O_RDONLY);
//	fd2 = open("holy_bible.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		write(1, line, strlen(line));
		write(1, "\n", 1);
		free (line);
	}
	free (line);
	close (fd);
//	close (fd2);

	return 0;
}
