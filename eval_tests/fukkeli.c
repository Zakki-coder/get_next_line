#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *line = (char *)malloc(sizeof(char) * 18000000);
	char *buf = (char *)malloc(sizeof(char) * 18000000);
	int fd;
//	int fd2;
	int ret = 1;
	int i = 0;
	int t_i = 0;

	fd = open("holy_bible_noeol.txt", O_RDONLY);
//	fd2 = open("holy_bible.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);
	while ((ret = read(fd, line, 1)) == 1)
	{
		if (line[t_i] != '\n')
		{
			buf[i] = line[t_i];
			++i;
			++t_i;
		}
		t_i = 0;
	}
	free (line);
	close (fd);
//	close (fd2);

	return 0;
}
