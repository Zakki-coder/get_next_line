#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include "../get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *line;
	char buf[10];
	int ret;

	line = NULL;
	int fd_1 = open("./test1", O_RDONLY);
	int fd_2 = open("./test2", O_RDONLY);
	if(fd_1 == -1)
		return -1;
	ret = get_next_line(fd_1, &line);
	printf("%s\n", line);
	ret = get_next_line(fd_2, &line);
	printf("%s\n", line);
	ret = get_next_line(fd_1, &line);
	printf("%s\n", line);
	ret = get_next_line(fd_2, &line);
	printf("%s\n", line);
	return (0);
}
