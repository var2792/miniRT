/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 12:45:35 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/30 12:45:45 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_nbrlen(long int nt)
{
	int len;

	len = 1;
	while (nt / 10 > 0)
	{
		len++;
		nt /= 10;
	}
	return (len);
}

static long int	deca_size(long int size)
{
	long int	d;
	int			j;

	d = 1;
	j = 0;
	while (j < size - 2)
	{
		d *= 10;
		j++;
	}
	return (d);
}

static void		str_and(char *str, int len, long int nbr)
{
	long int	dec;
	int			i;
	long int	nt;
	long int	t;

	i = 0;
	nt = nbr;
	if (nbr < 0)
	{
		dec = deca_size(len - 1);
		str[i++] = '-';
		nt *= -1;
	}
	else
		dec = deca_size(len);
	while (i < len)
	{
		t = nt / dec;
		str[i++] = t + 48;
		nt = nt % dec;
		if (dec == 1)
			break ;
		dec /= 10;
	}
	str[i] = '\0';
}

char			*ft_itoa(int nbr)
{
	long int	n;
	int			len;
	char		*str;

	n = nbr;
	len = 0;
	if (nbr < 0)
		len = 2 + ft_nbrlen(-1 * n);
	else
		len = 1 + ft_nbrlen(n);
	str = NULL;
	if (!(str = (char*)malloc(sizeof(char) * len)))
		return (NULL);
	if (str != NULL)
		str_and(str, len, n);
	return (str);
}
