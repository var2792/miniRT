/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:01:06 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 17:01:10 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*st;
	int		i;

	i = -1;
	while (c != s[++i])
		if (s[i] == '\0')
			break ;
	if (c != s[i])
		return (NULL);
	st = (char*)s;
	while (i--)
		st++;
	return (st);
}
