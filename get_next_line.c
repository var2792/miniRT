/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:06 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/05 13:55:10 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		read_in_buff(int fd, char **s, char *buff, int *n)
{
	while (ft_findchr(*s, '\n') < 0 && *n > 0)
	{
		if ((*n = read(fd, buff, BUFFER_SIZE)) < 0)
		{
			free(s[fd]);
			return (-1);
		}
		buff[*n] = '\0';
		*s = join_temp(*s, buff);
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	char			*buff;
	static char		*s[1024];
	int				n;
	int				fl;

	n = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buff = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	fl = read_in_buff(fd, &s[fd], buff, &n);
	free(buff);
	if (fl < 0)
		return (fl);
	if (s[fd])
	{
		unite_stnext(line, &s[fd]);
		divide_static(&s[fd]);
		return ((n == 0) ? 0 : 1);
	}
	if (!(*line = malloc(sizeof(char) * 1)))
		return (-1);
	**line = '\0';
	free(s[fd]);
	return ((n == 0) ? 0 : 1);
}
