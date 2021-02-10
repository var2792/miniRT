/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 16:27:10 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/29 16:27:13 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	void	*s;

	s = (char*)ft_memchr(src, (unsigned char)c, n);
	i = 0;
	if (s == NULL)
	{
		ft_memcpy(dst, src, n);
		return (NULL);
	}
	while (i < (size_t)(s - src + 1))
	{
		((char*)dst)[i] = ((char*)src)[i];
		i++;
	}
	return (dst + i);
}
