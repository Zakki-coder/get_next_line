#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

/*
int main(int argc, char **argv)
{
	char *line = NULL;
	int fd;
	int ret = 1;

//	printf("%d\n", get_next_line(42, &line));
//	free (line);
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
		while ((ret = get_next_line(fd, &line)) > 0)
		{
	//		printf("ret: %d\n", ret);
			printf("%s\n", line);
			free (line);
		}
		close (fd);
	}
	return 0;
}
*/

int main (void)
{
	char *line = NULL;
	int fd1 = open("one_big_fat_line.txt", O_RDONLY);
//	int fd2 = open("5test_two_line_16", O_RDONLY);
//	int ret;
	
	while (get_next_line(fd1, &line) == 1)
	{
		printf("%s\n", line);
	}
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("ret: %d\n", ret);
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("ret 2: %d\n", ret);
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("ret 3: %d\n", ret);
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("%d\n", ret);
//	ret = get_next_line(fd2, &line);
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("%d\n", ret);
//	printf("%s\n", line);
//	printf("%d\n", ret);
//	ret = get_next_line(fd1, &line);
//	printf("%s\n", line);
//	printf("%d\n", ret);
//	ret = get_next_line(fd2, &line);
//	printf("%s\n", line);
//	printf("%d\n", ret);
	return (0);
	}

