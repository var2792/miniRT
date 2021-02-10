# include "parse_file.h"

void	spase_com_sep(char **line)
{
	while (ft_check_isspace(**line) || **line == ',')
		(*line)++;
}

int		parse_resplution(char **line, t_objscene *scene)
{
	(*line)++;
	scene->r.x = ft_atoi_float(line);
	scene->r.y = ft_atoi_float(line);
	if (scene->r.x <= 0 || scene->r.y <= 0)
		return (1);
	scene->r.x = (scene->r.x > 1920) ? 1920 : scene->r.x;
	scene->r.y = (scene->r.y > 1080) ? 1080 : scene->r.y;
	scene->r.is = 1;
	return (0);
}

int		parse_ambient(char **line, t_objscene *scene)
{
	(*line)++;
	scene->a.rat_amlig = ft_atoi_float(line);
	if (scene->a.rat_amlig < 0 || scene->a.rat_amlig > 1)
		return (1);
	scene->a.rat_amlig = (scene->a.rat_amlig < 0.75) ? 0.1 : scene->a.rat_amlig;
	scene->a.color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->a.color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->a.color.z = ft_atoi_float(line);
	if (check_color(scene->a.color))
		return (1);
	return (0);
}

int		parse_camera(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line)++;
	while (scene->c[i].is)
		i++;
	scene->c[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].coord.z = ft_atoi_float(line);
	scene->c[i].normal.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].normal.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].normal.z = ft_atoi_float(line);
	if (check_normal(scene->c[i].normal))
		return (0);
	if ((scene->c[i].fov = ft_atoi_float(line)) < 0 || scene->c[i].fov > 180)
		return (1);
	scene->c[i].is = 1;
	return (0);
	(void)scene;
}

int		parse_light(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line)++;
	while (scene->l[i].is)
		i++;
	scene->l[i].coord.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].coord.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].coord.z = ft_atoi_float(line);
	if ((scene->l[i].brirat = ft_atoi_float(line)) < 0 || scene->l[i].brirat > 1)
		return (1);
	scene->l[i].color.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].color.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].color.z = ft_atoi_float(line);
	if (check_color(scene->l[i].color))
		return (1);
	scene->l[i].is = 1;
	return (0);
	(void)scene;
}
