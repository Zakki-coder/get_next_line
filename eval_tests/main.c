#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)//int argc, char **argv)
{
	char *line = NULL;
	int fd;
	int fd2;
	int ret = 1;

//	if (get_next_line(42, &line) != -1)
//		printf("ERROR should return -1 with fd 42");
//	free (line);
//	if (get_next_line(-1, &line) != -1)
//		printf("ERROR should return -1 with fd -1");
//	free (line);
//	if (argc == 1)
//		fd = 0;
//	else
	fd = open("holy_bible_noeol.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);
	fd2 = open("holy_bible_noeol.txt", O_RDONLY);
	while ((ret = get_next_line(fd2, &line)) == 1)
	{
		write(fd, line, strlen(line));
//		write(1, "\n", 1);
		free (line);
	}
	system("diff holy_bible_noeol.txt holy_bible_noeol.txt.mine > holy_bible_noeol.txt.diff");
	free (line);
	close (fd);
	close (fd2);

	return 0;
}