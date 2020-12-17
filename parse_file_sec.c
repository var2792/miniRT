# include "parse_file.h"

int parse_sphere(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->sp[i].is)
		i++;
	scene->sp[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].coord.z = ft_atoi_float(line);
	scene->sp[i].diam = ft_atoi_float(line);
	scene->sp[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].color.z = ft_atoi_float(line);
	scene->sp[i].is = 1;
	return (0);
	(void)scene;
}

int parse_plane(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->pl[i].is)
		i++;
	scene->pl[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].coord.z = ft_atoi_float(line);
	scene->pl[i].normal.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].normal.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].normal.z = ft_atoi_float(line);
	scene->pl[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].color.z = ft_atoi_float(line);
	scene->pl[i].is = 1;
	return (0);
	(void)scene;
}

int parse_square(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->sq[i].is)
		i++;
	scene->sq[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].coord.z = ft_atoi_float(line);
	scene->sq[i].normal.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].normal.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].normal.z = ft_atoi_float(line);
	scene->sq[i].size = ft_atoi_float(line);
	scene->sq[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].color.z = ft_atoi_float(line);
	scene->sq[i].is = 1;
	return (0);
	(void)scene;
}

int parse_cylinder(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->cy[i].is)
		i++;
	scene->cy[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].coord.z = ft_atoi_float(line);
	scene->cy[i].normal.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].normal.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].normal.z = ft_atoi_float(line);
	scene->cy[i].diam = ft_atoi_float(line);
	scene->cy[i].heig = ft_atoi_float(line);
	scene->cy[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].color.z = ft_atoi_float(line);
	scene->cy[i].is = 1;
	return (0);
	(void)scene;
}

int parse_triangle(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->tr[i].is)
		i++;
	scene->tr[i].coord_fir.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_fir.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_fir.z = ft_atoi_float(line);
	scene->tr[i].coord_sec.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_sec.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_sec.z = ft_atoi_float(line);
	scene->tr[i].coord_thi.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_thi.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].coord_thi.z = ft_atoi_float(line);
	scene->tr[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].color.z = ft_atoi_float(line);
	scene->tr[i].is = 1;
	return (0);
	(void)scene;
}
