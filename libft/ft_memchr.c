/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 13:58:47 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/29 13:58:49 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*st;
	size_t			i;

	i = 0;
	st = (unsigned char *)s;
	while (i < n)
	{
		if ((unsigned char)c == st[i])
			return (st + i);
		i++;
	}
	return (NULL);
}
