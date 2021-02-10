/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:54:52 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 12:54:56 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		raz;
	size_t	i;

	i = 0;
	raz = 0;
	while ((i < n) && (raz == 0) &&
		((unsigned char)(s1[i]) != '\0' ||
		(unsigned char)(s2[i]) != '\0'))
	{
		raz = (unsigned char)(s1[i]) - (unsigned char)(s2[i]);
		i++;
	}
	return (raz);
}
