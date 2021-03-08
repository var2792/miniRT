/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_float.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:53:32 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 12:53:46 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_check_isspace(char s)
{
	if (s == '\t' || s == 32)
		return (1);
	return (0);
}

static int	cicle_num(char **str, float *num, int m)
{
	int		f;
	float	n;
	int		dec;

	f = 0;
	dec = 1;
	while ((**str > 47 && **str < 58) && **str)
	{
		if (f)
		{
			dec *= 10;
			n = (**str - 48);
			*num = *num + m * n / dec;
		}
		else
			*num = *num * 10 + m * (**str - 48);
		(*str)++;
		if (**str == '.')
		{
			f = 1;
			(*str)++;
		}
	}
	return (dec);
}

float		ft_atoi_float(char **str)
{
	float	num;
	int		m;
	int		dec;

	num = 0;
	m = 1;
	while (ft_check_isspace(**str) && **str != '\0')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			m = -1;
		(*str)++;
	}
	dec = cicle_num(str, &num, m);
	num = round(num * dec) / dec;
	return (num);
}
