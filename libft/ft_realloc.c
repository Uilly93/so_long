/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnocchi <wnocchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:00:08 by wnocchi           #+#    #+#             */
/*   Updated: 2024/02/06 17:08:56 by wnocchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*realloc(void *ptr, size_t size)
{
	void *reallocated;

	reallocated = ft_calloc(1, sizeof(void *));
	if(!reallocated)
		return (NULL);
	ft_memcpy(reallocated, (void *)ptr, size);
	free(ptr);
	return (reallocated);
}