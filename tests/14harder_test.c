#include <string.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include "get_next_line.h"

int				main(void)
{
	char		*line;
	int			fd;
	int			ret;
	int			count_lines;

	fd = open("14harder_test", O_RDONLY);
	if (fd > 2)
	{
		count_lines = 0;
		line = NULL;
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (count_lines == 0 && strcmp(line, "1234567") != 0)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 1 && strcmp(line, "12345678") != 0)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 2 && strcmp(line, "123456789") != 0)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 3 && ret != 1)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 4 && strcmp(line, "This is after newline") != 0)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 5 && ret != 1)
				printf("Error on line: %d\n", count_lines);
			if (count_lines == 6 && ret != 1)
				printf("Error on line: %d\n", count_lines);
			count_lines++;
			free(line);
			if (count_lines > 50)
				break ;
		}
		close(fd);
		if (count_lines != 7)
			printf("-> must have returned '1' six times instead of %d time(s)\n", count_lines);
	}
	if (count_lines == 7)
		printf("OK\n");
	else
		printf("An ERROR\n");
	return (0);
}
