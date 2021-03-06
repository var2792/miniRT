#include "../incs/funct_def.h"

int	belong_to_sphere(t_general *gen, t_sphere *sp)
{
	float t[2];
	t_vector p;
	t_list *lstsp;
	int fl;

	fl = 1;
	p = sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo);
	t[1] = find_discr(p, sum_vs(1, gen->scene.cdo, -1, sp->cd), sp->d * sp->d / 4, &(t[0]));
	if (t[0] >= 1 && fl > 0)
		p = sum_vs(1, gen->scene.cdo, t[0], p);
	else if (t[1] >= 1 && fl > 0)
		p = sum_vs(1, gen->scene.cdo, t[1], p);

	if (fl > 0)
		if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] < 1 - EPS && t[1] < 1 - EPS))
			fl = 0;
	gen->cl = (fl == 1) ? light_change_sp(*gen, p, *sp, (int)gen->pix.z) : gen->cl;

	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.sp, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_sphere(gen, lstsp->content);
	return (gen->cl);
}

int		see_sp_util(t_scene scene, t_vector ptr, float t[])
{
	t_vector p;

	if (t[0] > EPS)
		p = sum_vs(1, scene.cdo, t[0], sum_vs(1, scene.cdv, -1, scene.cdo));
	else if (t[1] > EPS)
		p = sum_vs(1, scene.cdo, t[1], sum_vs(1, scene.cdv, -1, scene.cdo));
	else
		return (0);

	if (len_vec(sum_vs(1, p, -1, scene.cdo)) - len_vec(sum_vs(1, ptr, -1, scene.cdo)) < -EPS)
		return (1);
	return (0);
}

int		check_see_sp(t_general gen, t_vector ptr, int num_sp)
{
	float t[2];
	int i;
	t_vector p;
	t_list *temp;
	t_sphere *sp;

	i = 0;
	temp = gen.objs.sp;
	while (temp)
	{
		if (i != num_sp)
		{
			sp = temp->content;
			p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
			if ((t[1] = find_discr(p, sum_vs(1, gen.scene.cdo, -1, sp->cd), sp->d * sp->d / 4, &(t[0]))) > EPS)
				if (see_sp_util(gen.scene, ptr, t))
					return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

float		check_shadow_sp(t_light num_l, int num_sp, t_scobjs objects, t_vector p)
{
	float t[2];
	int i;
	t_list *temp;
	t_sphere *sp;

	temp = objects.sp;
	i = 0;
	while (temp)
	{
		if (i != num_sp)
		{
			sp = temp->content;
			if ((t[1] = find_discr(sum_vs(1, p, -1, num_l.cd), sum_vs(1, num_l.cd, -1, sp->cd), sp->d * sp->d / 4, &(t[0]))) > EPS)
				if ((t[0] > EPS && t[0] < 1 - EPS) || (t[1] > EPS && t[1] <  1 - EPS))
					return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float	light_change_sp(t_general gen, t_vector p, t_sphere sp, int num_sp)
{
	float bright;
	float res_br;
	t_list *temp;
	t_light *num_l;
	t_vector sum_lig;

	res_br = gen.objs.a.rat;
	temp = gen.objs.l;
	ft_write_xyz(&sum_lig, 0 ,0, 0);
	while (temp)
	{
		num_l = temp->content;
		if ((bright = dot_prv(sum_vs(-1, p, 1, sp.cd), sum_vs( 1, p, -1, num_l->cd)) / len_vec(sum_vs(1, p, -1, sp.cd)) / len_vec(sum_vs( 1, p, -1, num_l->cd))) < 0)
			bright = 0;
		res_br += num_l->br * bright * check_shadow(*num_l, num_sp, gen.objs, p);
		sum_lig = sum_vs( 1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	res_br = (res_br > 1) ? 1 : res_br;
	sp.cl = sum_vs(res_br, sum_vs(0.4, sp.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	correct_color(&(sp.cl));
	//objects.sp[i].cl.x *= res_br;
	//objects.sp[i].cl.y *= res_br;		//не цветное освещение
	//objects.sp[i].cl.z *= res_br;
	return (ft_colorvec_unsint(1, sp.cl));
}
