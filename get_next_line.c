/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/16 01:09:44 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>     //DELEETEEE
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct	s_hash_node
{
	void				*value;
	int					key;
	struct	s_hash_node	*next;
}						t_hashNode;

t_hashNode *ft_new_hash_node(int	key, void *value)
{
	t_hashNode *new_node;

	new_node = (t_hashNode *)malloc(sizeof(t_hashNode));
	(*new_node).key = key;
	(*new_node).value = value;
	(*new_node).next = NULL;

	return (new_node);
}

void	ft_addhash(t_hashNode **hashlst, t_hashNode *new)
{
	t_hashNode	*new_next;

			if (new == NULL || hashlst == NULL)
				return ;
			if (*hashlst == NULL)
			{
				*hashlst = new;
				return ;
			}
			new_next = *hashlst;
			*hashlst = new;
			(*new).next = new_next;
}

		int calculate_hash (int fd)
		{
			return (fd % 100);
		}

char **search_key_return_buff(int key, t_hashNode *head)
{
	while (head != NULL && head->key != key)
		head = head->next;
	if (head == NULL)
		return (NULL);
	else
		return ((char **)&(head->value));
}

int get_next_line(const int fd, char **line)
{
	//Can line be NULL?	
	size_t len;
	size_t i;
	size_t t_i;
	//Create hashlist for defaul of 1024 filedescriptors, but scalable to infinity
//	static char temp_array[BUFF_SIZE] = {'\0'};
//	char *temp_buf = temp_array;
	static t_hashNode *hash[100] = {NULL};
	char **temp_buf = (char **)malloc(sizeof(temp_buf));

	i = 0;
	len = 1;
	t_i = 0;
//	if (temp_array[0] == '\0')
//		len = read(fd, temp_buf, BUFF_SIZE);
	
	*line  = (char *)malloc(sizeof(**line) * BUFF_SIZE + 1);
	temp_buf = search_key_return_buff(fd, hash[calculate_hash(fd)]);
	if (temp_buf == NULL || **temp_buf == '\n')
	{
		temp_buf = (char **)malloc(sizeof(*temp_buf));
		*temp_buf = (char *)malloc(sizeof(**temp_buf) * BUFF_SIZE);
		len = read(fd, *temp_buf, BUFF_SIZE);
		ft_addhash(&hash[calculate_hash(fd)], ft_new_hash_node(fd, (void *)*temp_buf));
	}
	while (len && *(*temp_buf + t_i) != '\n')
	{
		//write to line until \n
	//	while (len && temp_buf[t_i] != '\n')
	//	{
			(*line)[i++] = (*temp_buf)[t_i++];
	//		printf("%s\n", *line);				//DELETEEE
	//	}
		//if no \n found alloc more space 
		if (t_i == BUFF_SIZE && len && (*temp_buf)[t_i] != '\n')
		{
			len = read(fd, *temp_buf, BUFF_SIZE);
			*line = ft_realloc(*line, i, i + len + 1);
			t_i = 0;
		}
			//protect also the real function
		//protect
		//t_i = 0;
	}
		//Better size for memmove?
		//*(*temp_buf) = 127;
		//**temp_buf += 1;
		//printf("Hello: %s\n", *temp_buf);
		//ft_memmove(*temp_buf, *temp_buf + (t_i), BUFF_SIZE - t_i);
		//what should it do with multiple \n
			//repeat
	return (1);
}
