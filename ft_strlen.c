/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 17:04:54 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/22 17:05:03 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlen(void *str)
{
	unsigned long i;

	i = 0;
	if ((unsigned char *)str == 0)
		return (0);
	while (((unsigned char *)str)[i] != '\0')
		i++;
	return (i);
}
