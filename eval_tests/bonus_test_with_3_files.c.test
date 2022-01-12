#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

int main(void)
{	
	int fd1;
	int fd2;
	int fd3;
	char *line;
	int ret;

	fd1 = open("8test_two_line_4", O_RDONLY);		
	fd2 = open("2test_two_line_8", O_RDONLY);		
	fd3 = open("5test_two_line_16", O_RDONLY);		

	printf("Call two times, reaches eof\n");
	ret = get_next_line(fd1, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);
	ret = get_next_line(fd2, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);
	ret = get_next_line(fd3, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);
	ret = get_next_line(fd1, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);
	ret = get_next_line(fd2, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);
	ret = get_next_line(fd3, &line);
	printf("%s\tret: %d\n", line, ret);
	assert(ret == 1);
	free (line);

	printf("Call twice more, after eof is reached\n");
	ret = get_next_line(fd1, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	ret = get_next_line(fd2, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	ret = get_next_line(fd3, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	ret = get_next_line(fd1, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	ret = get_next_line(fd2, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	ret = get_next_line(fd3, &line);
	printf("%sret: %d\n", line, ret);
	assert(ret == 0);
	free (line);
	return (0);
}	
