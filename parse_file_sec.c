# include "parse_file.h"

int parse_sphere(char **line, t_scobjs *scene)
{
	t_sphere *cont;
	t_list *new;

	(*line) += 2;
	cont = malloc(sizeof(*cont));
	cont->cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd.z = ft_atoi_float(line);
	cont->d = ft_atoi_float(line);
	cont->cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cl.y = ft_atoi_float(line);
	if (!spase_com_sep(line))
		return (1);
	cont->cl.z = ft_atoi_float(line);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->sp), new);
	return (0);
	(void)scene;
}

int parse_plane(char **line, t_scobjs *scene)
{
	t_plane *cont;
	t_list *new;

	(*line) += 2;
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
		return (1);
	cont->cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cl.y = ft_atoi_float(line);
	if (!spase_com_sep(line))
		return (1);
	cont->cl.z = ft_atoi_float(line);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->pl), new);
	return (0);
	(void)scene;
}

int parse_square(char **line, t_scobjs *scene)
{
	t_square *cont;
	t_list *new;

	(*line) += 2;
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
		return (1);
	cont->s = ft_atoi_float(line);
	cont->cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cl.y = ft_atoi_float(line);
	if (!spase_com_sep(line))
		return (1);
	cont->cl.z = ft_atoi_float(line);
	if (check_color(cont->cl))
		return (1);
	find_point_sq(*cont, &(cont->ps));
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->sq), new);
	/*printf("+++++++++++++++++++\n");
	printf("%f %f %f %f\n", scene->sq[i].nm.x, scene->sq[i].nm.y, scene->sq[i].nm.z, scene->sq[i].s);
	printf("%f %f %f\n", scene->sq[i].ps[0].x, scene->sq[i].ps[0].y, scene->sq[i].ps[0].z);
	printf("%f %f %f\n", scene->sq[i].ps[1].x, scene->sq[i].ps[1].y, scene->sq[i].ps[1].z);
	printf("%f %f %f\n", scene->sq[i].ps[2].x, scene->sq[i].ps[2].y, scene->sq[i].ps[2].z);
	printf("%f %f %f\n", scene->sq[i].ps[3].x, scene->sq[i].ps[3].y, scene->sq[i].ps[3].z);
	printf("------------------\n");*/
	return (0);
	(void)scene;
}

int parse_cylinder(char **line, t_scobjs *scene)
{
	t_cylinder *cont;
	t_list *new;

	(*line) += 2;
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
		return (1);
	cont->d = ft_atoi_float(line);
	cont->h = ft_atoi_float(line);
	cont->cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cl.y = ft_atoi_float(line);
	if (!spase_com_sep(line))
		return (1);
	cont->cl.z = ft_atoi_float(line);
	if (check_color(cont->cl))
		return (1);
	//printf("Cy %f %f %f\n", cont->cl.x, cont->cl.y, cont->cl.z);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->cy), new);
	return (0);
	(void)scene;
}

int parse_triangle(char **line, t_scobjs *scene)
{
	t_triangle *cont;
	t_list *new;

	(*line) += 2;
	cont = malloc(sizeof(*cont));
	cont->cd1.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd1.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd1.z = ft_atoi_float(line);
	cont->cd2.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd2.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd2.z = ft_atoi_float(line);
	cont->cd3.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd3.y = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cd3.z = ft_atoi_float(line);
	cont->cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	cont->cl.y = ft_atoi_float(line);
	if (!spase_com_sep(line))
		return (1);
	cont->cl.z = ft_atoi_float(line);
	if (check_color(cont->cl))
		return (1);
	cont->nm = cross_prv(sum_vs(1, cont->cd2, -1, cont->cd1), sum_vs(1, cont->cd3, -1, cont->cd1));
	cont->nm = sum_vs(1 / len_vec(cont->nm), cont->nm, 0, cont->nm);
	//printf("Tr %f %f %f\n", scene->tr[i].nm.x, scene->tr[i].nm.y, scene->tr[i].nm.z);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->tr), new);
	return (0);
}
