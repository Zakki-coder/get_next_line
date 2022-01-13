/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 00:30:29 by jniemine          #+#    #+#             */
/*   Updated: 2022/01/13 21:40:15 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# define BUFF_SIZE 8

typedef struct s_hash_node
{
	void				*v;
	int					key;
	size_t				p;
	struct s_hash_node	*next;
}						t_hashNode;

typedef struct s_line
{
	size_t	i;
	size_t	space;
	char	**line;
}			t_line;

int	get_next_line(const int fd, char **line);

#endif
