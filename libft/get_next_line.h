/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 13:55:13 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/05 13:55:16 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "general_minirt.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# define BUFFER_SIZE 1

int			get_next_line(int fd, char **line);
int			ft_findchr(char *st, char c);
char		*ft_join_free(char *s1, const char *s2);
void		divide_static(char **st);
void		unite_stnext(char **line, char **st);
#endif
