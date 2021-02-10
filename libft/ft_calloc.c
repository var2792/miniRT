/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 16:34:15 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/31 16:34:17 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	void	*res;
	size_t	i;

	if (!(res = malloc(size * num)))
		return (NULL);
	i = 0;
	while (i < num * size)
		((char*)res)[i++] = '\0';
	return (res);
}
