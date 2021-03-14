/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

float	bright_cy(t_cylinder cy, t_light num_l, t_vector p, int fl)
{
	float		bright;
	t_vector	newnm;

	if (fl != 4)
	{
		bright = dot_prv(cy.nm, sum_vs(1, p, -1, cy.cd))
		/ dot_prv(cy.nm, cy.nm);
		newnm = sum_vs(1, cy.cd, bright, cy.nm);
		if ((bright = dot_prv(sum_vs(-1, p, 1, newnm),
		sum_vs(1, p, -1, num_l.cd)) / len_vec(sum_vs(1, p, -1, newnm))
		/ len_vec(sum_vs(1, p, -1, num_l.cd))) < 0)
			bright = 0;
	}
	else
		bright = perpend_heads(cy, p, num_l)
		/ len_vec(sum_vs(1, p, -1, num_l.cd));
	return (bright);
}

float	light_change_cy(t_general gen, t_vector p, int num_cy, int fl)
{
	float		res_br;
	t_list		*temp;
	t_light		*num_l;
	t_vector	sum_lig;
	t_cylinder	*cy;

	res_br = gen.objs.a.rat;
	temp = gen.objs.l;
	cy = ft_lstnum(gen.objs.cy, num_cy)->content;
	ft_write_xyz(&sum_lig, 0, 0, 0);
	while (temp)
	{
		num_l = temp->content;
		res_br += num_l->br * bright_cy(*cy, *num_l, p, fl) *
		check_shadow(*num_l, num_cy + 400, gen.objs, p);
		sum_lig = sum_vs(1, sum_lig, num_l->br * res_br, num_l->cl);
		temp = temp->next;
	}
	return (rescolobj(cy->cl, sum_lig, gen.objs.a.cl, res_br));
}

int		belong_cy(t_general gen, t_cylinder cy, t_vector *p)
{
	float	t[2];
	int		fl;

	t[1] = find_discr(cross_prv(sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo),
	cy.nm), sum_vs(1, cross_prv(gen.scene.cdo, cy.nm), -1, cross_prv(cy.cd,
	cy.nm)), dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]));
	fl = t[1] < 1 - EPS ? 0 : 1;
	if (t[0] > 1 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[0],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 2;
	}
	if (t[1] > 1 && fl > 0 && fl != 2)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 3;
	}
	return (fl);
}

int		belong_to_cylinder(t_general *gen, t_cylinder *cy)
{
	t_list		*lstsp;
	t_vector	p;
	int			fl;

	fl = belong_cy(*gen, *cy, &p);
	fl = belong_to_cyhead0(*gen, *cy, &p, fl);
	fl = belong_to_cyhead1(*gen, *cy, &p, fl);
	if (fl > 0 && check_see_objs(*gen, p, 400 + (int)gen->pix.z))
		fl = 0;
	gen->cl = (fl > 1) ? light_change_cy(*gen, p,
	(int)gen->pix.z, fl) : gen->cl;
	gen->pix.z += 1;
	if ((lstsp = ft_lstnum(gen->objs.cy, (int)gen->pix.z)) != NULL)
		gen->cl = belong_to_cylinder(gen, lstsp->content);
	return (gen->cl);
}
