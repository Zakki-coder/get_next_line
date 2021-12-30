/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/30 22:40:38 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_hashNode *ft_new_hash_node(int	key, void *value)
{
	t_hashNode *new_node;

	new_node = (t_hashNode *)ft_memalloc(sizeof(t_hashNode));
	if (new_node == NULL)
		return (NULL);
	(*new_node).key = key;
	if (value != NULL)
		(*new_node).value = value;
	else
		(*new_node).value = (void *)ft_memalloc(sizeof(signed char) * (BUFF_SIZE + 1));
	if ((*new_node).value == NULL)
		return (NULL);
	(*new_node).position = 0;
	(*new_node).eof = 0;
	(*new_node).next = NULL;
	return (new_node);
}

t_list *search_key_return_buff(int key, t_list *head)
{
	while (head != NULL && ((t_hashNode *)head->content)->key != key)
		head = head->next;
	if (head == NULL)
		return (NULL);
	else
		return (head);
}
/*
//Make a reader function, takes node as param, returns return of read?
int reader (t_hashNode *node)
{	
	int temp_buf;
	int len;

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
		ft_lstadd(&hash[hash_code], ft_lstnew(ft_new_hash_node(fd, (void *)temp_buf), sizeof(t_hashNode)));
		node = (t_hashNode *)hash[hash_code]->content;
	}
	else
	{
		len = read(fd, temp_buf, BUFF_SIZE);
		if (len == -1)
			return (-1);
		if (len < BUFF_SIZE)
			temp_buf[len + 1] = -1;
	}
}
*/
int get_next_line(const int fd, char **line)
{
	ssize_t len;
	size_t i;
	size_t t_i;
	int hash_code;
	static t_list *hash[100] = {NULL};
	t_hashNode *node;
	t_list *lst_node;

	i = 0;
	len = 1;
	hash_code = fd % 100;
	if (line == NULL)
		return (-1);
	*line  = (char *)ft_memalloc(sizeof(**line) * BUFF_SIZE);
	if (*line == NULL)
		return (-1);
	lst_node = search_key_return_buff(fd, hash[hash_code]);
	if (lst_node == NULL)
	{
		node = ft_new_hash_node(fd, NULL);
		if (node == NULL)
			return (-1);
		len = read(fd, node->value, BUFF_SIZE);
		if (len == -1)
		{
			free (node->value);
			free (node);
			return (-1);
		}
		if (len < BUFF_SIZE)
			((signed char *)node->value)[len] = -1;
		if (len == 0)
			return (0);
		lst_node = ft_lstnew(node, sizeof(t_hashNode));
		ft_lstadd(&hash[hash_code], lst_node);
		free (node);
	}
	node = (t_hashNode *)lst_node->content;
	t_i = node->position;
	if (node->eof)
	{
		free (node->value);
		ft_lstdelany(&hash[hash_code], lst_node);
		free (lst_node);
		return (0);
	}
	while (((signed char *)node->value)[t_i] >= 0 && len && ((signed char *)node->value)[t_i] != '\n')
	{
		if (t_i == BUFF_SIZE && len && ((signed char *)node->value)[t_i] != '\n')
		{
			len = read(fd, node->value, BUFF_SIZE);
			if (len == -1)
			{
				free (node->value);
				free (node);
				return (-1);
			}
			if (len < BUFF_SIZE)
				((signed char *)node->value)[len] = -1;
//			if (len == 0)
//				return (0);
			*line = ft_realloc(*line, i, i + len + 1);
			if (line == NULL)
				return (-1);
			t_i = 0;
		}
			if (((signed char *)node->value)[t_i] != '\n' && ((signed char *)node->value)[t_i] >= 0)
				(*line)[i++] = ((signed char *)node->value)[t_i++];
	}
	if (((signed char *)node->value)[t_i] == '\n')
		node->position = (++t_i);
	if (((signed char *)node->value)[t_i] == -1)
		node->eof = 1;
	return (1);
}
