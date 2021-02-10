/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:30:27 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/31 13:30:29 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	if (!(res = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len && start + i < ft_strlen(s))
	{
		res[i] = s[start + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
