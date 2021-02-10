/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 14:23:39 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/29 14:23:41 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;
	char	*ld;
	char	*ls;

	d = (char*)dst;
	s = (char*)src;
	ld = (char*)dst + len - 1;
	ls = (char*)src + len - 1;
	if (!d && !s)
		return (NULL);
	if (d < s)
	{
		while (len--)
			*d++ = *s++;
	}
	else
	{
		while (len--)
			*ld-- = *ls--;
	}
	return (dst);
}
