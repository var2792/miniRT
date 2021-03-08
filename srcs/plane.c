/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		check_see_pl(t_general gen, t_vector ptr, int num_pl)
{
	int			i;
	float		t;
	t_vector	p;
	t_list		*temp;
	t_plane		*pl;

	i = -1;
	temp = gen.objs.pl;
	while (temp)
	{
		if (++i != num_pl)
		{
			pl = temp->content;
			t = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, gen.scene.cdo);
			t /= dot_prv(pl->nm, gen.scene.cdv)
			- dot_prv(pl->nm, gen.scene.cdo);
			p = sum_vs(1, gen.scene.cdo, t,
			sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
			if ((t > 1 && t < 200) && len_vec(sum_vs(1, p, -1,
			gen.scene.cdo)) < len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
				return (1);
		}
		temp = temp->next;
	}
	return (0);
}

float	check_shadow_pl(t_light num_l, int num_pl, t_scobjs objects, t_vector p)
{
	float	t;
	int		i;
	t_list	*temp;
	t_plane	*pl;

	temp = objects.pl;
	i = 0;
	while (temp)
	{
		if (i != num_pl)
		{
			pl = temp->content;
			t = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, num_l.cd);
			t /= dot_prv(pl->nm, p) - dot_prv(pl->nm, num_l.cd);
			if (t > 0 && t < 1)
				return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float	light_change_pl(t_general gen, t_vector p, t_plane pl, int npl)
{
	float		br;
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
		br = perpend_to_plane(pl.cd, pl.nm, num_l->cd)
		/ len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * br * (check_orient(pl.nm, num_l->cd,
		gen.scene.cdo, p) ? check_shadow(*num_l, npl + 100, gen.objs, p) : 0);
		sum_lig = sum_vs(1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	return (rescolobj(pl.cl, sum_lig, gen.objs.a.cl, res_br));
}

int		belong_to_plane(t_general *gen, t_plane *pl)
{
	t_vector	p;
	t_list		*lstsp;
	float		t;

	t = dot_prv(pl->nm, pl->cd) - dot_prv(pl->nm, gen->scene.cdo);
	t /= dot_prv(pl->nm, gen->scene.cdv) - dot_prv(pl->nm, gen->scene.cdo);
	if (t > 1)
	{
		p = sum_vs(1, gen->scene.cdo, t,
		sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo));
		if (!check_see_objs(*gen, p,
		100 + (int)gen->pix.z) && (t > 1 && t < 200))
			gen->cl = light_change_pl(*gen, p, *pl, (int)gen->pix.z);
	}
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.pl, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_plane(gen, lstsp->content);
	return (gen->cl);
}
