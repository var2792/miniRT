#include "light_change.h"

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
		if ((bright = dot_prv(sum_vs(-1 / len_vec(sum_vs(1, p, -1, sp.cd)), p, 1 / len_vec(sum_vs( 1, p, -1, sp.cd)), sp.cd), sum_vs( 1, p, -1, num_l->cd)) / len_vec(sum_vs( 1, p, -1, num_l->cd))) < 0)
			bright = 0;

		res_br += num_l->br * bright * check_shadow(*num_l, num_sp, gen.objs, p);

		sum_lig.x += num_l->br * num_l->cl.x * res_br;
		sum_lig.y += num_l->br * num_l->cl.y * res_br;
		sum_lig.z += num_l->br * num_l->cl.z * res_br;
		temp = temp->next;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	sp.cl = sum_vs(res_br, sum_vs(0.4, sp.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	sp.cl.x = (sp.cl.x > 255) ? 255 : sp.cl.x;
	sp.cl.y = (sp.cl.y > 255) ? 255 : sp.cl.y;
	sp.cl.z = (sp.cl.z > 255) ? 255 : sp.cl.z;
	/*objects.sp[i].cl.x *= res_br;
	objects.sp[i].cl.y *= res_br;		//не цветное освещение
	objects.sp[i].cl.z *= res_br;*/
	return (ft_colorvec_unsint(1, sp.cl));
}

float	light_change_pl(t_general gen, t_vector p, t_plane pl, int num_pl)
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
		bright = 30 / len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * bright * (check_orient(pl.nm, num_l->cd, gen.scene.cdo, p) ? check_shadow(*num_l, num_pl + 100, gen.objs, p) : 0);

		sum_lig.x += num_l->br * num_l->cl.x * res_br;
		sum_lig.y += num_l->br * num_l->cl.y * res_br;
		sum_lig.z += num_l->br * num_l->cl.z * res_br;
		temp = temp->next;
	}

	if (res_br > 1)
		res_br = 1;

	pl.cl = sum_vs(res_br, sum_vs(0.4, pl.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	pl.cl.x = (pl.cl.x > 255) ? 255 : pl.cl.x;
	pl.cl.y = (pl.cl.y > 255) ? 255 : pl.cl.y;
	pl.cl.z = (pl.cl.z > 255) ? 255 : pl.cl.z;

	return(ft_colorvec_unsint(1, pl.cl));
	(void) p;
}

float	light_change_sq(t_general gen, t_vector p, t_square sq, int num_sq)
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
		bright = 20 / len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * bright * (check_orient(sq.nm, num_l->cd, gen.scene.cdo, p) ? check_shadow(*num_l, num_sq + 200, gen.objs, p) : 0);

		sum_lig.x += num_l->br * num_l->cl.x * res_br;
		sum_lig.y += num_l->br * num_l->cl.y * res_br;
		sum_lig.z += num_l->br * num_l->cl.z * res_br;
		temp = temp->next;
	}

	if (res_br > 1)
		res_br = 1;

	sq.cl = sum_vs(res_br, sum_vs(0.4, sq.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	sq.cl.x = (sq.cl.x > 255) ? 255 : sq.cl.x;
	sq.cl.y = (sq.cl.y > 255) ? 255 : sq.cl.y;
	sq.cl.z = (sq.cl.z > 255) ? 255 : sq.cl.z;

	return(ft_colorvec_unsint(1, sq.cl));
	(void) p;
}

float	light_change_tr(t_general gen, t_vector p, t_triangle tr, int num_tr)
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
		bright = 20 / len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * bright * (check_orient(tr.nm, num_l->cd, gen.scene.cdo, p) ? check_shadow(*num_l, num_tr + 300, gen.objs, p) : 0);

		sum_lig.x += num_l->br * num_l->cl.x * res_br;
		sum_lig.y += num_l->br * num_l->cl.y * res_br;
		sum_lig.z += num_l->br * num_l->cl.z * res_br;
		temp = temp->next;
	}

	if (res_br > 1)
		res_br = 1;

	tr.cl = sum_vs(res_br, sum_vs(0.4, tr.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	tr.cl.x = (tr.cl.x > 255) ? 255 : tr.cl.x;
	tr.cl.y = (tr.cl.y > 255) ? 255 : tr.cl.y;
	tr.cl.z = (tr.cl.z > 255) ? 255 : tr.cl.z;

	return(ft_colorvec_unsint(1, tr.cl));
	(void) p;
}

float	light_change_cy(t_general gen, t_vector p, int num_cy, int fl)
{
	float bright;
	float res_br;
	t_list *temp;
	t_light *num_l;
	t_vector sum_lig;
	t_cylinder *cys;
	t_cylinder cy;

	res_br = gen.objs.a.rat;
	temp = gen.objs.l;
	cys = ft_lstnum(gen.objs.cy, num_cy)->content;
	cy = *cys;
	ft_write_xyz(&sum_lig, 0 ,0, 0);
	while (temp)
	{
		num_l = temp->content;
		if (fl != 4)
		{
			bright = -dot_prv(cy.nm, sum_vs(1, cy.cd, -1, p)) / dot_prv(cy.nm, cy.nm);
			if ((bright = dot_prv(sum_vs(-1, p, 1, sum_vs(1, cy.cd, bright, cy.nm)), sum_vs( 1, p, -1, num_l->cd)) / len_vec(sum_vs(-1, p, 1, sum_vs(1, cy.cd, bright, cy.nm))) / len_vec(sum_vs( 1, p, -1, num_l->cd))) < 0)
				bright = 0;
		}
		else
			bright = 20 / len_vec(sum_vs(1, p, -1, num_l->cd));

		res_br += num_l->br * bright * check_shadow(*num_l, num_cy + 400, gen.objs, p);

		sum_lig.x += num_l->br * num_l->cl.x * res_br;
		sum_lig.y += num_l->br * num_l->cl.y * res_br;
		sum_lig.z += num_l->br * num_l->cl.z * res_br;
		temp = temp->next;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	cy.cl = sum_vs(res_br, sum_vs(0.4, cy.cl, 0.4, sum_lig), 0.2 * res_br, gen.objs.a.cl);
	cy.cl.x = (cy.cl.x > 255) ? 255 : cy.cl.x;
	cy.cl.y = (cy.cl.y > 255) ? 255 : cy.cl.y;
	cy.cl.z = (cy.cl.z > 255) ? 255 : cy.cl.z;
	return(ft_colorvec_unsint(1, cy.cl));
	(void) p;
}
