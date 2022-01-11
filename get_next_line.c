/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 14:21:44 by jniemine          #+#    #+#             */
/*   Updated: 2022/01/11 18:56:14 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

t_hashNode	*ft_new_hash_node(int key, void *value)
{
	t_hashNode	*new_node;

	new_node = (t_hashNode *)ft_memalloc(sizeof(t_hashNode));
	if (new_node == NULL)
		return (NULL);
	(*new_node).key = key;
	if (value != NULL)
		(*new_node).v = value;
	else
		(*new_node).v = (void *)ft_memalloc(sizeof(char) * (BUFF_SIZE + 1));
	if ((*new_node).v == NULL)
		return (NULL);
	(*new_node).p = 0;
	(*new_node).next = NULL;
	return (new_node);
}

int	reader(char **line, t_hashNode **node, size_t old_size)
{	
	ssize_t	len;

	if (*node == NULL)
		return (-1);
	len = read((*node)->key, (*node)->v, BUFF_SIZE);
	(*node)->p = 0;
	if (len == -1)
	{
		free ((*node)->v);
		free (*node);
		return (-1);
	}
	if (len < BUFF_SIZE)
		((signed char *)(*node)->v)[len] = -1;
	if (old_size > 0)
		*line = ft_realloc(*line, old_size, old_size + (len) + 1);
	if (*line == NULL)
		return (-1);
	return (len);
}

t_list	*search_for_key(int key, t_list **head, char **line, ssize_t *len)
{
	t_hashNode	*node;
	t_list		**lst_start;

	lst_start = head;
	if (*line == NULL)
		return (NULL);
	while (head != NULL && *head != NULL && (*head)->content != NULL
		&& ((t_hashNode *)(*head)->content)->key != key)
		*head = (*head)->next;
	if (*head == NULL || (*head)->content == NULL)
	{
		node = ft_new_hash_node(key, NULL);
		*len = reader(line, &node, 0);
		if (*len <= 0)
			return (NULL);
		*head = ft_lstnew(node, sizeof(t_hashNode));
		ft_lstadd(lst_start, *head);
		free (node);
	}
	return (*head);
}

int	write_to_line(char **line, size_t *i, t_list *lst_node, t_list **hash)
{
	int			newline;
	t_hashNode	*node;

	node = lst_node->content;
	newline = 0;
	while (((char *)node->v)[node->p] >= 0
	&& ((char *)node->v)[node->p] != '\n')
	{
		if (node->p == BUFF_SIZE && ((char *)node->v)[node->p] != '\n')
			if (reader(line, &node, *i) == -1)
				return (-1);
		while (node->p < BUFF_SIZE && ((char *)node->v)[node->p] != '\n'
		&& ((char *)node->v)[node->p] >= 0)
			(*line)[(*i)++] = ((char *)node->v)[node->p++];
	}
	if (node->p < BUFF_SIZE && ((char *)node->v)[node->p] == '\n' && ++node->p)
		newline = 1;
	if (*i > 0 || newline)
		return (1);
	free (node->v);
	ft_lstdelany(hash, lst_node);
	free (lst_node);
	return (0);
}

int	get_next_line(const int fd, char **line)
{
	ssize_t			len;
	size_t			i;
	static t_list	*hash[100] = {NULL};
	t_list			*lst_node;

	i = 0;
	len = 1;
	if (line == NULL)
		return (-1);
	*line = (char *)ft_memalloc(sizeof(**line) * BUFF_SIZE + 1);
	lst_node = search_for_key(fd, &(hash[fd % 100]), line, &len);
	if (len == 0)
		return (0);
	if (lst_node == NULL && len != 0)
		return (-1);
	return (write_to_line(line, &i, lst_node, &(hash[fd % 100])));
}
