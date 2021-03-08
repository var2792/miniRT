/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

static float	equal_tpl(t_triangle tr, t_scene scene)
{
	float t;

	t = dot_prv(tr.nm, tr.cd1) - dot_prv(tr.nm, scene.cdo);
	t /= dot_prv(tr.nm, scene.cdv) - dot_prv(tr.nm, scene.cdo);
	return (t);
}

int				check_see_tr(t_general gen, t_vector ptr, int num_tr)
{
	int			i;
	float		t;
	t_vector	p;
	t_list		*temp;
	t_triangle	*tr;

	i = -1;
	temp = gen.objs.tr;
	while (temp)
	{
		if (++i != num_tr)
		{
			tr = temp->content;
			t = equal_tpl(*tr, gen.scene);
			p = sum_vs(1, gen.scene.cdo, t,
			sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
			if (t > 1 && point_in_triangle(*tr, p))
				if (len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <
				len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
		}
		temp = temp->next;
	}
	return (0);
}

float			check_shadow_tr(t_light num_l, int num_tr,
t_scobjs objects, t_vector p)
{
	float		t;
	int			i;
	t_vector	pt;
	t_list		*temp;
	t_triangle	*tr;

	temp = objects.tr;
	i = 0;
	while (temp)
	{
		if (i != num_tr)
		{
			tr = temp->content;
			t = dot_prv(tr->nm, tr->cd1) - dot_prv(tr->nm, num_l.cd);
			t /= dot_prv(tr->nm, p) - dot_prv(tr->nm, num_l.cd);
			pt = sum_vs(1, num_l.cd, t, sum_vs(1, p, -1, num_l.cd));
			if (point_in_triangle(*tr, pt))
				if (t > EPS && t < 1)
					return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float			light_change_tr(t_general gen, t_vector p,
t_triangle tr, int num_tr)
{
	float		bright;
	float		res_br;
	t_list		*temp;
	t_light		*num_l;
	t_vector	sum_lig;

	res_br = gen.objs.a.rat;
	temp = gen.objs.l;
	ft_write_xyz(&sum_lig, 0, 0, 0);
	while (temp)
	{
		num_l = temp->content;
		bright = perpend_to_plane(tr.cd1, tr.nm, num_l->cd)
		/ len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * bright * (check_orient(tr.nm, num_l->cd,
		gen.scene.cdo, p) ? check_shadow(*num_l, num_tr + 300,
		gen.objs, p) : 0);
		sum_lig = sum_vs(1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	return (rescolobj(tr.cl, sum_lig, gen.objs.a.cl, res_br));
}

int				belong_to_triangle(t_general *gen, t_triangle *tr)
{
	t_vector	p;
	t_list		*lstsp;
	float		t;

	t = dot_prv(tr->nm, tr->cd1) - dot_prv(tr->nm, gen->scene.cdo);
	t /= dot_prv(tr->nm, gen->scene.cdv) - dot_prv(tr->nm, gen->scene.cdo);
	p = sum_vs(1, gen->scene.cdo, t,
	sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo));
	if (t > 1 && point_in_triangle(*tr, p))
		if (!check_see_objs(*gen, p, 300 + (int)gen->pix.z))
			gen->cl = light_change_tr(*gen, p, *tr, (int)gen->pix.z);
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.tr, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_triangle(gen, lstsp->content);
	return (gen->cl);
}
