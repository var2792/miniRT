# include "parse_file.h"

int parse_sphere(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->sp[i].is)
		i++;
	scene->sp[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].cd.z = ft_atoi_float(line);
	scene->sp[i].d = ft_atoi_float(line);
	scene->sp[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sp[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->sp[i].cl))
		return (1);
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
	scene->pl[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].cd.z = ft_atoi_float(line);
	scene->pl[i].nm.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].nm.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].nm.z = ft_atoi_float(line);
	if (check_normal(scene->pl[i].nm))
		return (1);
	scene->pl[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->pl[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->pl[i].cl))
		return (1);
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
	scene->sq[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].cd.z = ft_atoi_float(line);
	scene->sq[i].nm.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].nm.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].nm.z = ft_atoi_float(line);
	if (check_normal(scene->sq[i].nm))
		return (1);
	scene->sq[i].s = ft_atoi_float(line);
	scene->sq[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->sq[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->sq[i].cl))
		return (1);
	find_point_sq(scene->sq[i], &(scene->sq[i].ps));
	scene->sq[i].is = 1;
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

int parse_cylinder(char **line, t_objscene *scene)
{
	int i;

	i = 0;
	(*line) += 2;
	while (scene->cy[i].is)
		i++;
	scene->cy[i].cd.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].cd.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].cd.z = ft_atoi_float(line);
	scene->cy[i].nm.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].nm.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].nm.z = ft_atoi_float(line);
	if (check_normal(scene->cy[i].nm))
		return (1);
	scene->cy[i].d = ft_atoi_float(line);
	scene->cy[i].h = ft_atoi_float(line);
	scene->cy[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->cy[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->cy[i].cl))
		return (1);
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
	scene->tr[i].cd1.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd1.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd1.z = ft_atoi_float(line);
	scene->tr[i].cd2.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd2.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd2.z = ft_atoi_float(line);
	scene->tr[i].cd3.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd3.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cd3.z = ft_atoi_float(line);
	scene->tr[i].cl.x = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cl.y = ft_atoi_float(line);
	spase_com_sep(line);
	scene->tr[i].cl.z = ft_atoi_float(line);
	if (check_color(scene->tr[i].cl))
		return (1);
	scene->tr[i].nm = cross_prv(sum_vs(1, scene->tr[i].cd2, -1, scene->tr[i].cd1), sum_vs(1, scene->tr[i].cd3, -1, scene->tr[i].cd1));
	scene->tr[i].nm = sum_vs(1 / len_vec(scene->tr[i].nm), scene->tr[i].nm, 0, scene->tr[i].nm);
	//printf("Tr %f %f %f\n", scene->tr[i].nm.x, scene->tr[i].nm.y, scene->tr[i].nm.z);
	scene->tr[i].is = 1;
	return (0);
}
