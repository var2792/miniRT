/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 17:27:57 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 17:39:03 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*temp;

	i = ft_strlen(s);
	while ((unsigned char)c != '\0' &&
		(unsigned char)c != (unsigned char)(s[--i]))
		if (i <= 0)
			break ;
	if ((i == 0 && (unsigned char)c != s[i]) || (s[0] == '\0' && c != '\0'))
		return (NULL);
	temp = (unsigned char*)s;
	while (i > 0 && i--)
		temp++;
	return ((char*)temp);
}
