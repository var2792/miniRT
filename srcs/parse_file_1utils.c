#include "../incs/funct_def.h"

int		sep_fl(float *num, char **line, int fl)
{
	while (ft_check_isspace(**line))
		(*line)++;
	if (fl && **line == ',')
		(*line)++;
	while (ft_check_isspace(**line))
		(*line)++;
	if (ft_isdigit(**line) || **line == '-' || **line == '+')
	{
		*num = ft_atoi_float(line);
		return (0);
	}
	else
		return (1);

}

int		parse_resplution(char **line, t_scobjs *scene)
{
	(*line)++;
	scene->r.x = ft_atoi_dinam(line);
	scene->r.y = ft_atoi_dinam(line);
	if (scene->r.x <= 0 || scene->r.y <= 0)
		return (1);
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
	if (sep_fl(&(scene->a.cl.x), line, 0) || sep_fl(&(scene->a.cl.y), line, 1) || sep_fl(&(scene->a.cl.z), line, 1))
		return (1);
	//printf("%f %f %f\n", scene->a.cl.x, scene->a.cl.y, scene->a.cl.z);
	if (check_color(scene->a.cl))
		return (1);
	scene->a.is = 1;
	return (0);
}

int		parse_camera(char **line, t_scobjs *scene)
{
	t_camera *cont;
	t_list *new;

	(*line)++;
	cont = malloc(sizeof(*cont));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1) || sep_fl(&(cont->cd.z), line, 1))
		return (1);
	if (sep_fl(&(cont->nm.x), line, 0) || sep_fl(&(cont->nm.y), line, 1) || sep_fl(&(cont->nm.z), line, 1))
		return (1);
	if (check_normal(cont->nm))
		return (1);
	if ((cont->fov = ft_atoi_float(line)) < 0 || cont->fov > 180)
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->c), new);
	return (0);
}

int		parse_light(char **line, t_scobjs *scene)
{
	t_light *cont;
	t_list *new;

	(*line)++;
	cont = malloc(sizeof(*cont));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1) || sep_fl(&(cont->cd.z), line, 1))
		return (1);
	if ((cont->br = ft_atoi_float(line)) < 0 || cont->br > 1)
		return (1);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1) || sep_fl(&(cont->cl.z), line, 1))
		return (1);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->l), new);
	return (0);
}
