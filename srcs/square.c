/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

static float	equal_tpl(t_square sq, t_scene scene)
{
	float t;

	t = dot_prv(sq.nm, sq.cd) - dot_prv(sq.nm, scene.cdo);
	t /= dot_prv(sq.nm, scene.cdv) - dot_prv(sq.nm, scene.cdo);
	return (t);
}

int				check_see_sq(t_general gen, t_vector ptr, int num_sq)
{
	int			i;
	float		t;
	t_vector	p;
	t_list		*temp;
	t_square	*sq;

	i = -1;
	temp = gen.objs.sq;
	while (temp)
	{
		if (++i != num_sq)
		{
			sq = temp->content;
			t = equal_tpl(*sq, gen.scene);
			p = sum_vs(1, gen.scene.cdo, t,
			sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
			if (t > 1 && point_in_square(*sq, p))
				if (len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <
				len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
					return (1);
		}
		temp = temp->next;
	}
	return (0);
}

float			check_shadow_sq(t_light num_l, int num_sq,
t_scobjs objects, t_vector p)
{
	float		t;
	int			i;
	t_vector	pt;
	t_list		*temp;
	t_square	*sq;

	temp = objects.sq;
	i = 0;
	while (temp)
	{
		if (i != num_sq)
		{
			sq = temp->content;
			t = dot_prv(sq->nm, sq->cd) - dot_prv(sq->nm, num_l.cd);
			t /= dot_prv(sq->nm, p) - dot_prv(sq->nm, num_l.cd);
			pt = sum_vs(1, num_l.cd, t, sum_vs(1, p, -1, num_l.cd));
			if (point_in_square(*sq, pt))
				if (t > EPS && t < 1)
					return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}

float			light_change_sq(t_general gen, t_vector p,
t_square sq, int num_sq)
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
		bright = perpend_to_plane(sq.cd, sq.nm, num_l->cd)
		/ len_vec(sum_vs(1, p, -1, num_l->cd));
		res_br += num_l->br * bright * (check_orient(sq.nm, num_l->cd,
		gen.scene.cdo, p) ? check_shadow(*num_l, num_sq + 200,
		gen.objs, p) : 0);
		sum_lig = sum_vs(1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	return (rescolobj(sq.cl, sum_lig, gen.objs.a.cl, res_br));
}

int				belong_to_square(t_general *gen, t_square *sq)
{
	t_vector	p;
	t_list		*lstsp;
	float		t;

	t = dot_prv(sq->nm, sq->cd) - dot_prv(sq->nm, gen->scene.cdo);
	t /= dot_prv(sq->nm, gen->scene.cdv) - dot_prv(sq->nm, gen->scene.cdo);
	p = sum_vs(1, gen->scene.cdo, t,
	sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo));
	if (t > 1 && point_in_square(*sq, p))
		if (!check_see_objs(*gen, p, 200 + (int)gen->pix.z))
			gen->cl = light_change_sq(*gen, p, *sq, (int)gen->pix.z);
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.sq, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_square(gen, lstsp->content);
	return (gen->cl);
}
