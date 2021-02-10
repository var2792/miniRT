/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:28:32 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/31 13:28:37 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	unsigned char w;

	w = (unsigned char)c;
	write(fd, &w, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	int n;

	n = 0;
	if (s)
	{
		while (s[n])
			n++;
		write(fd, s, n + 1);
	}
}

void	ft_putendl_fd(char *s, int fd)
{
	int n;

	n = 0;
	if (s)
	{
		while (s[n])
			n++;
		write(fd, s, n);
		write(fd, "\n", 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	w;
	int		d;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n *= -1;
		write(fd, "-", 1);
	}
	d = 1;
	while (n / d > 9)
		d *= 10;
	while (d > 0)
	{
		w = 48 + n / d;
		write(fd, &w, 1);
		n = n % d;
		d /= 10;
	}
}
