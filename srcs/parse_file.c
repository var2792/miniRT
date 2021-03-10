/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		ft_check_input_chars(char **line, t_scobjs *scene)
{
	if ((*line)[0] == 'R')
		return (parse_resplution(line, scene));
	if ((*line)[0] == 'A')
		return (parse_ambient(line, scene));
	if ((*line)[0] == 'c' && (*line)[1] != 'y')
		return (parse_camera(line, scene));
	if ((*line)[0] == 'l')
		return (parse_light(line, scene));
	if ((*line)[0] == 's' && (*line)[1] == 'p')
		return (parse_sphere(line, scene));
	if ((*line)[0] == 'p' && (*line)[1] == 'l')
		return (parse_plane(line, scene));
	if ((*line)[0] == 's' && (*line)[1] == 'q')
		return (parse_square(line, scene));
	if ((*line)[0] == 'c' && (*line)[1] == 'y')
		return (parse_cylinder(line, scene));
	if ((*line)[0] == 't' && (*line)[1] == 'r')
		return (parse_triangle(line, scene));
	return (1);
}

void	ft_null_scene(t_scobjs *scene)
{
	scene->r.is = 0;
	scene->a.is = 0;
	scene->a.rat = 0;
	ft_write_xyz(&(scene->a.cl), 255, 255, 255);
	ft_write_xyz(&(scene->orig_cam), 0, 0, 1);
	scene->c = NULL;
	scene->l = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->sq = NULL;
	scene->tr = NULL;
	scene->cy = NULL;
}

int		check_name_file(char *argv)
{
	int	i;
	int	k;

	i = 0;
	if (argv[0] == '.' && argv[1] == '.' && argv[2] == '/')
		k = 3;
	else
		k = 0;
	while (argv[i + k] && argv[i + k] != '.')
		i++;
	if (!argv[i + k] || i < 1 + k)
		return (1);
	else if (argv[i + k + 1] && argv[i + k + 1] != 'r')
		return (1);
	else if (argv[i + k + 2] && argv[i + k + 2] != 't')
		return (1);
	else if (argv[i + k + 3] != '\0')
		return (1);
	return (0);
}

int		parse_lines(int fd, t_scobjs *objs)
{
	int		n;
	int		len;
	char	*line;
	char	*save_line;

	n = 1;
	while (n > 0)
	{
		n = get_next_line(fd, &line);
		save_line = line;
		len = ft_strilen(line);
		if (*line && len > 1)
		{
			while (ft_check_isspace(*line))
				line++;
			len = ft_check_input_chars(&line, objs);
			while (ft_check_isspace(*line))
				line++;
			if (len || *line != 0)
				return (errors_mes(2, &save_line));
		}
		free(save_line);
	}
	return (0);
}

int		parse_file(t_scobjs *objs, char *argv)
{
	int fd;

	if (check_name_file(argv))
		return (errors_mes(4, 0));
	if ((fd = open(argv, O_RDWR)) < 0)
		return (errors_mes(5, 0));
	ft_null_scene(objs);
	if (parse_lines(fd, objs))
		return (1);
	if (!objs->r.is)
		return (errors_mes(3, 0));
	close(fd);
	return (0);
}
