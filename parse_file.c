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
	scene->a.is = 1;
	return (0);
}

int		parse_camera(char **line, t_scobjs *scene)
{
	int i;
	t_camera *cont;
	t_list *new;

	i = 0;
	(*line)++;
	cont = malloc(sizeof(*cont));
	cont->cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd.z = ft_atoi_float(line);
	cont->nm.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->nm.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->nm.z = ft_atoi_float(line);
	if (check_normal(cont->nm))
		return (0);
	if ((cont->fov = ft_atoi_float(line)) < 0 || cont->fov > 180)
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->c), new);
	return (0);
	(void)i;
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
