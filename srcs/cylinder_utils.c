/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		check_head_orient(t_vector pcy, t_cylinder cy, t_light num_l)
{
	t_vector	p;
	t_vector	h;
	float		t;

	h = sum_vs(1, cy.cd, -cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t /= dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	p = sum_vs(1, num_l.cd, t, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, num_l.cd))
	< len_vec(sum_vs(1, pcy, -1, num_l.cd)) - EPS)
		return (0);
	h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t /= dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	p = sum_vs(1, num_l.cd, t, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, num_l.cd))
	< len_vec(sum_vs(1, pcy, -1, num_l.cd)) - EPS)
		return (1);
	return (2);
}

float	perpend_heads(t_cylinder cy, t_vector p, t_light num_l)
{
	t_vector	h;

	if (check_head_orient(p, cy, num_l) == 0)
		h = sum_vs(1, cy.cd, -cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	if (check_head_orient(p, cy, num_l) == 1)
		h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	return (perpend_to_plane(h, cy.nm, num_l.cd));
}

int		belong_to_cyhead0(t_general gen, t_cylinder cy, t_vector *pcy, int fl)
{
	t_vector	p;
	t_vector	h;
	float		t;

	h = sum_vs(1, cy.cd, -cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, gen.scene.cdo);
	t /= dot_prv(cy.nm, gen.scene.cdv) - dot_prv(cy.nm, gen.scene.cdo);
	p = sum_vs(1, gen.scene.cdo, t,
	sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (t > 1 && len_vec(sum_vs(1, p, -1, h)) < cy.d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <
		len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
}

int		belong_to_cyhead1(t_general gen, t_cylinder cy, t_vector *pcy, int fl)
{
	t_vector	p;
	t_vector	h;
	float		t;

	h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t = dot_prv(cy.nm, h) - dot_prv(cy.nm, gen.scene.cdo);
	t /= dot_prv(cy.nm, gen.scene.cdv) - dot_prv(cy.nm, gen.scene.cdo);
	p = sum_vs(1, gen.scene.cdo, t,
	sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (t > 1 && len_vec(sum_vs(1, p, -1, h)) < cy.d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <
		len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
}
