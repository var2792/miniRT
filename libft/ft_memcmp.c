/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:14:22 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/29 12:14:32 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *lhs, const void *rhs, size_t n)
{
	int		raz;
	int		i;

	i = -1;
	raz = 0;
	while ((++i < (int)n) && (raz == 0))
		raz = ((unsigned char*)lhs)[i] - ((unsigned char*)rhs)[i];
	return (raz);
}
