/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/20 22:05:43 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h> // DELT

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

t_hashNode *search_key_return_buff(int key, t_hashNode *head)
{
	while (head != NULL && head->key != key)
		head = head->next;
	if (head == NULL)
		return (NULL);
	else
		return (head);
}

int get_next_line(const int fd, char **line)
{
	ssize_t len;
	size_t i;
	size_t t_i;
	int hash_code;
	static t_hashNode *hash[100] = {NULL};
	int *temp_buf;
	t_hashNode *node;

	i = 0;
	len = 1;
	hash_code = fd % 100;
	
	*line  = (char *)malloc(sizeof(**line) * BUFF_SIZE + 1);
	if (*line == NULL)
		return (-1);
	node = search_key_return_buff(fd, hash[hash_code]);
	if (node == NULL)
	{
		temp_buf = (int *)malloc(sizeof(sizeof(*temp_buf) * BUFF_SIZE + 1));
		if (temp_buf == NULL)
			return (-1);
		len = read(fd, temp_buf, BUFF_SIZE);
		if (len == -1)
			return (-1);
		if (len < BUFF_SIZE)
			temp_buf[len + 1] = -1;
		ft_addhash(&hash[hash_code], ft_new_hash_node(fd, (void *)temp_buf));
		node = hash[hash_code];
	}
	temp_buf = (int *)node->value;
	t_i = node->position;
	while (temp_buf[t_i] >= 0 && len && ((char *)temp_buf)[t_i] != '\n')
	{
		if (t_i == BUFF_SIZE && len && ((char *)temp_buf)[t_i] != '\n')
		{
			len = read(fd, temp_buf, BUFF_SIZE);
			if (len == -1)
				return (-1);
			if (len < BUFF_SIZE)
				temp_buf[len + 1] = -1;
			*line = ft_realloc(*line, i, i + len + 1);
			t_i = 0;
		}
			if (temp_buf[t_i] >= 0)
				(*line)[i++] = ((char *)temp_buf)[t_i++];
	}
	if (temp_buf[t_i] < 0)
		return (0);
	node->position = ++t_i;
	return (1);
}
