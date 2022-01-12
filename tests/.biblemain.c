#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int fd1;
	int fd2;
	int ret;
	char *line;
	int argc = 1;

	if (argc == 1)
	{
	fd1 = open("holy_bible_noeol.txt", O_RDONLY);
	printf("fd: %d\n", fd1);
	fd2 = open("holy_bible.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);
	
	while((ret = get_next_line(fd1, &line)) == 1)
	{
		write(fd2, line, strlen(line));
		write(fd2, "\n", 1);
		free (line);
	}
	close(fd1);
	close(fd2);
	}
	return (0);
}
