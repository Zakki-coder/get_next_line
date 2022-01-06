#ifndef GET_NEXT_LINE_HEADER_H
# define GET_NEXT_LINE_HEADER_H

#include "libft.h"
#define BUFF_SIZE 8

typedef struct	s_hash_node
{
	void				*value;
	int					key;
	int					eof;
	size_t				p;
	struct	s_hash_node	*next;
}						t_hashNode;

int get_next_line(const int fd, char **line);

#endif
