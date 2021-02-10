/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:54:13 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 12:54:18 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t j;
	size_t n;
	size_t num;

	if (size == 0)
		return (ft_strlen(src));
	num = (ft_strlen(dest) < size) ? ft_strlen(dest) : size;
	n = 0;
	while (dest[n] && n < size)
		n++;
	j = 0;
	while (src[j] && n + j < size - 1)
	{
		dest[j + n] = src[j];
		j++;
	}
	if (n + j < size)
		dest[j + n] = '\0';
	return (num + ft_strlen(src));
}
