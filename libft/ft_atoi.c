/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 12:53:32 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/28 12:53:46 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_isspace(char s)
{
	if (s == '\t' || s == 32 || s == '\n'
		|| s == '\v' || s == '\f' || s == '\r')
		return (1);
	return (0);
}

int			ft_atoi(const char *str)
{
	int			i;
	long int	num;
	int			m;

	i = 0;
	num = 0;
	m = 1;
	while (ft_isspace(str[i]) && str[i] != '\0')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			m = -1;
		i++;
	}
	while ((str[i] > 47 && str[i] < 58) && str[i])
	{
		if (num == -2147483648 || num > 2147483647)
			return (-1);
		if (num == 2147483647 || num < -2147483648)
			return (0);
		num = num * 10 + m * (str[i] - 48);
		i++;
	}
	return (num);
}

int			ft_atoi_dinam(char **str)
{
	long int	num;
	int			m;

	num = 0;
	m = 1;
	while (ft_isspace(**str) && **str != '\0')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			m = -1;
		(*str)++;
	}
	while ((**str > 47 && **str < 58) && **str)
	{
		if (num == -2147483648 || num > 2147483647)
			return (-1);
		if (num == 2147483647 || num < -2147483648)
			return (0);
		num = num * 10 + m * (**str - 48);
		(*str)++;
	}
	return (num);
}
