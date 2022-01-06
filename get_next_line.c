/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2022/01/06 18:23:32 by jniemine         ###   ########.fr       */
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
	(*new_node).p = 0;
	(*new_node).eof = 0;
	(*new_node).next = NULL;
	return (new_node);
}

int reader (char **line, t_hashNode **node, size_t old_size, ssize_t *len)
{	
//	ssize_t len;

	if (*node == NULL)
		return (-1);
	*len = read((*node)->key, (*node)->value, BUFF_SIZE);
	(*node)->p = 0;
	if (*len == -1)
	{
		free ((*node)->value);
		free (*node);
		return (-1);
	}
	if (*len < BUFF_SIZE)
		((signed char *)(*node)->value)[*len] = -1;
	if (old_size > 0)
		*line = ft_realloc(*line, old_size, old_size + (*len) + 1);
	if (*line == NULL)
		return (-1);
	return (*len);
}

t_list *search_key_return_buff(int key, t_list **head, char **line, ssize_t *len)
{
	t_hashNode	*node;
	t_list		**lst_start;

	lst_start = head;
	if (*line == NULL)
		return (NULL);
	while (head != NULL && *head != NULL && (*head)->content != NULL && ((t_hashNode *)(*head)->content)->key != key)
		*head = (*head)->next;
	if (*head == NULL || (*head)->content == NULL)
	{
		node = ft_new_hash_node(key, NULL);
		*len = reader(line, &node, 0, len); 
		if(*len <= 0)
			return (NULL);
		*head = ft_lstnew(node, sizeof(t_hashNode));
		ft_lstadd(lst_start, *head);
		free (node);
	}
	return (*head);
	}

int get_next_line(const int fd, char **line)
{
	ssize_t len;
	size_t i;
	int newline;
	static t_list *hash[100] = {NULL};
	t_hashNode *node;
	t_list *lst_node;

	newline = 0;
	i = 0;
	len = 1;
	if (line == NULL)
		return (-1);
	*line  = (char *)ft_memalloc(sizeof(**line) * BUFF_SIZE + 1);
	lst_node = search_key_return_buff(fd, &(hash[fd % 100]), line, &len);
	if (len == 0)
		return (0);
	if (lst_node == NULL && len != 0)
		return (-1);
	node = (t_hashNode *)lst_node->content;
	while (((signed char *)node->value)[node->p] >= 0 && len && ((signed char *)node->value)[node->p] != '\n')
	{
		if (node->p == BUFF_SIZE && len && ((signed char *)node->value)[node->p] != '\n')
		{
			if(reader(line, &node, i, &len) == -1)
				return (-1);
		}
		while (node->p < BUFF_SIZE && ((signed char *)node->value)[node->p] != '\n' && ((signed char *)node->value)[node->p] >= 0)
			(*line)[i++] = ((signed char *)node->value)[node->p++];
	}
	if (node->p < BUFF_SIZE && ((signed char *)node->value)[node->p] == '\n')
	{
		newline = 1;
		node->p += 1;
	}
	if (i > 0 || newline)
		return (1);	
	free (node->value);
	ft_lstdelany(&hash[fd % 100], lst_node);
	free (lst_node);
	return (0);
}
