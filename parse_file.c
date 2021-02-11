# include "parse_file.h"

void	spase_com_sep(char **line)
{
	while (ft_check_isspace(**line) || **line == ',')
		(*line)++;
}

int		parse_resplution(char **line, t_scobjs *scene)
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

int		parse_ambient(char **line, t_scobjs *scene)
{
	(*line)++;
	scene->a.rat = ft_atoi_float(line);
	if (scene->a.rat < 0 || scene->a.rat > 1)
		return (1);
	scene->a.rat = (scene->a.rat < 0.75) ? 0.1 : scene->a.rat;
	scene->a.cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->a.cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->a.cl.z = ft_atoi_float(line);
	if (check_color(scene->a.cl))
		return (1);
	return (0);
}

int		parse_camera(char **line, t_scobjs *scene)
{
	int i;

	i = 0;
	(*line)++;
	while (scene->c[i].is)
		i++;
	scene->c[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].cd.z = ft_atoi_float(line);
	scene->c[i].nm.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].nm.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->c[i].nm.z = ft_atoi_float(line);
	if (check_normal(scene->c[i].nm))
		return (0);
	if ((scene->c[i].fov = ft_atoi_float(line)) < 0 || scene->c[i].fov > 180)
		return (1);
	scene->c[i].is = 1;
	return (0);
	(void)scene;
}

int		parse_light(char **line, t_scobjs *scene)
{
	int i;

	i = 0;
	(*line)++;
	while (scene->l[i].is)
		i++;
	scene->l[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].cd.z = ft_atoi_float(line);
	if ((scene->l[i].br = ft_atoi_float(line)) < 0 || scene->l[i].br > 1)
		return (1);
	scene->l[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->l[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->l[i].cl))
		return (1);
	scene->l[i].is = 1;
	return (0);
	(void)scene;
}
