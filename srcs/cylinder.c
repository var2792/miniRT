#include "../incs/funct_def.h"

int		belong_to_cylinder(t_general *gen, t_cylinder *cy)
{
	t_list *lstsp;
	t_vector p;
	int fl;

	fl = belong_cy(*gen, *cy, &p);

	//if (fl > 1)
		//if (fabs(len_vec(cross_prv(sum_vs(1, p, -1, cy->cd), cy->nm)) / len_vec(cy->nm) - cy->d / 2) < 0.01)
			//printf("%i\t%f %f %f\n", fl, p.x, p.y, p.z);
	fl = belong_to_cyhead0(*gen, *cy, &p, fl);
	fl = belong_to_cyhead1(*gen, *cy, &p, fl);

	//if (fl > 0 && check_see_objs(*gen, p, 400 + (int)gen->pix.z))
		//fl = 0;

	//gen->cl = (fl > 1) ? ft_colorvec_unsint(1, cy->cl) : gen->cl;
	gen->cl = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z, fl) : gen->cl;

	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.cy, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_cylinder(gen, lstsp->content);
	return (gen->cl);
}

int		belong_cy(t_general gen, t_cylinder cy, t_vector *p)
{
	int fl;

	fl = 1;
	t_vector newnm;
	int	k;
	k = 0;
	if (fabs(cy.nm.x) > 0.01)
	{
		k = 1;
		if (len_vec(ft_write_xyz(&newnm, 0, cy.nm.y, cy.nm.z)) < 0.01)
			ft_write_xyz(&newnm, 0, 1, 0);
		rot_cy_cord(&gen, &cy, &newnm, 0);
	}
	fl = belong_cy2(gen, cy, p);

	if (k == 1)
		rot_cy_cord(&gen, &cy, &newnm, p);
	return (fl);
}

int		check_see_cy(t_general gen, t_vector ptr, int num_cy)
{
	int i;
	int fl;
	t_vector p;
	t_list *temp;
	t_cylinder *cy;

	i = 0;
	temp = gen.objs.cy;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			fl = see_cy(gen, *cy, &p);

			if (fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
				return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}

float		check_shadow_cy(t_light num_l, int num_cy, t_scobjs objects, t_vector pt)
{
	int i;
	t_list *temp;
	t_cylinder *cy;

	temp = objects.cy;
	i = 0;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			//gen->scene.cdv->pt, gen->scene.cdo->num_l.cd
			if (shadow_cy(*cy, num_l, pt))
				return (0);
			if (shadow_cyhead0(*cy, pt, num_l) || shadow_cyhead1(*cy, pt, num_l))
				return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float	light_change_cy(t_general gen, t_vector p, int num_cy, int fl)
{
	float res_br;
	t_list *temp;
	t_light *num_l;
	t_vector sum_lig;
	t_cylinder *cy;

	res_br = gen.objs.a.rat;
	temp = gen.objs.l;
	cy = ft_lstnum(gen.objs.cy, num_cy)->content;
	ft_write_xyz(&sum_lig, 0 ,0, 0);
	while (temp)
	{
		num_l = temp->content;
		res_br += num_l->br * bright_cy(*cy, *num_l, p, fl) * check_shadow(*num_l, num_cy + 400, gen.objs, p);

		sum_lig = sum_vs( 1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	return (rescolcy(cy->cl, sum_lig, gen.objs.a.cl, res_br));
}
