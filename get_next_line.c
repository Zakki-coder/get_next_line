/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/16 23:44:40 by jniemine         ###   ########.fr       */
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
	size_t					position;
	struct	s_hash_node	*next;
}						t_hashNode;

t_hashNode *ft_new_hash_node(int	key, void *value)
{
	t_hashNode *new_node;

	new_node = (t_hashNode *)malloc(sizeof(t_hashNode));
	(*new_node).key = key;
	(*new_node).value = value;
	(*new_node).position = 0;
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

t_hashNode *search_key_return_buff(int key, t_hashNode *head)
{
	while (head != NULL && head->key != key)
		head = head->next;
	if (head == NULL)
		return (NULL);
	else
		return ((head));
}
//TODO IMPLEMENT WITH ONLY POSITION REMOVE MEMMOVE
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
	t_hashNode *node = (t_hashNode *)malloc(sizeof(node));

	i = 0;
	len = 1;
//	if (temp_array[0] == '\0')
//		len = read(fd, temp_buf, BUFF_SIZE);
	
	*line  = (char *)malloc(sizeof(**line) * BUFF_SIZE + 1);
	node = search_key_return_buff(fd, hash[calculate_hash(fd)]);
	if (node == NULL /*|| **temp_buf == '\n'*/)
	{
		temp_buf = (char **)malloc(sizeof(*temp_buf));
		*temp_buf = (char *)malloc(sizeof(**temp_buf) * BUFF_SIZE);
		len = read(fd, *temp_buf, BUFF_SIZE);
		ft_addhash(&hash[calculate_hash(fd)], ft_new_hash_node(fd, (void *)*temp_buf));
		node = hash[calculate_hash(fd)];
	}
	*temp_buf = node->value;
	t_i = 0;
	int position = node->position;
	while (len && *(*temp_buf + t_i) != '\n')
	{
		//write to line until \n
	//	while (len && temp_buf[t_i] != '\n')
	//	{
			(*line)[i++] = (*temp_buf)[t_i++];
			position++;
	//		printf("%s\n", *line);				//DELETEEE
	//	}
		//if no \n found alloc more space 
		//this never activates when reading from buff and buff_size > word
		if (position == BUFF_SIZE && len && (*temp_buf)[t_i] != '\n')
		{
			len = read(fd, *temp_buf, BUFF_SIZE);
			*line = ft_realloc(*line, i, i + len + 1);
			t_i = 0;
			position = 0;
		}
			//protect also the real function
		//protect
		//t_i = 0;
	}
		(*line)[i] = (*temp_buf)[t_i];
		//Better size for memmove?
		//*(*temp_buf) = 127;
		//**temp_buf += 1;
		//printf("Hello: %s\n", *temp_buf);
		ft_memmove(*temp_buf, *temp_buf + (++t_i), BUFF_SIZE - t_i);
		node->position = ++position;
		//what should it do with multiple \n
			//repeat
	return (1);
}
