/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jniemine <jniemine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:04:01 by jniemine          #+#    #+#             */
/*   Updated: 2021/12/05 20:17:03 by jniemine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_realloc(void *old_ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (old_ptr == NULL)
	{
		new_ptr = (void *)malloc(new_size);
		return (new_ptr);
	}
	if (old_size == 0)
	{
		new_ptr = (void *)malloc(new_size);
		free(old_ptr);
		old_ptr = NULL;
		return (new_ptr);
	}
	new_ptr = (void *)malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);
	ft_memcpy(new_ptr, old_ptr, old_size);
	free(old_ptr);
	old_ptr = NULL;
	return (new_ptr);
}
