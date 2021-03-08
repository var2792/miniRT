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

float			bright_cy(t_cylinder cy, t_light num_l, t_vector p, int fl)
{
	float		bright;
	t_vector	newnm;

	if (fl != 4)
	{
		bright = dot_prv(cy.nm, sum_vs(1, p, -1,
		cy.cd)) / dot_prv(cy.nm, cy.nm);
		newnm = sum_vs(1, cy.cd, bright, cy.nm);
		if ((bright = dot_prv(sum_vs(-1, p, 1, newnm),
		sum_vs(1, p, -1, num_l.cd)) / len_vec(sum_vs(-1, p, 1, newnm)) /
		len_vec(sum_vs(1, p, -1, num_l.cd))) < 0)
			bright = 0;
	}
	else
		bright = 20 / len_vec(sum_vs(1, p, -1, num_l.cd));
	return (bright);
}

int				shadow_cy(t_cylinder cy, t_light num_l, t_vector pt)
{
	float		t[2];
	t_vector	p;
	t_vector	newnm;

	if (fabs(cy.nm.x) > EPS)
	{
		if (len_vec(ft_write_xyz(&newnm, 0, cy.nm.y, cy.nm.z)) < 0.01)
			ft_write_xyz(&newnm, 0, 1, 0);
		rot_shadow_cy(&num_l, &cy, &newnm, &pt);
	}
	p = sum_vs(1, pt, -1, num_l.cd);
	if ((t[1] = find_discr(cross_prv(p, cy.nm), sum_vs(1, cross_prv(num_l.cd,
	cy.nm), -1, cross_prv(cy.cd, cy.nm)),
	dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]))) > EPS)
	{
		if ((t[0] > EPS && t[0] < 1 - EPS) || (t[1] < 1 - EPS))
		{
			p = sum_vs(1, num_l.cd, (t[0] > EPS && t[0] < 1 - EPS) ?
			t[0] : t[1], sum_vs(1, pt, -1, num_l.cd));
			if (len_vec(sum_vs(1, p, -1, cy.cd)) <=
			sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
				return (1);
		}
	}
	return (0);
}

int				see_cy(t_general gen, t_cylinder cy, t_vector *p)
{
	float		t[2];
	int			fl;
	t_vector	newnm;
	int			k;

	k = 0;
	if (fabs(cy.nm.x) > EPS)
	{
		k = 1;
		if (len_vec(ft_write_xyz(&newnm, 0, cy.nm.y, cy.nm.z)) < 0.01)
			ft_write_xyz(&newnm, 0, 1, 0);
		rot_cy_cord(&gen, &cy, &newnm, 0);
	}
	*p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
	t[1] = find_discr(cross_prv(*p, cy.nm), sum_vs(1, cross_prv(gen.scene.cdo,
	cy.nm), -1, cross_prv(cy.cd, cy.nm)),
	dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]));
	fl = t[1] < EPS ? 0 : 1;
	if (t[0] > EPS && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[0],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <=
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 2;
	}
	if (t[1] > EPS && fl != 2 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <=
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 3;
	}
	if (k == 1)
		rot_cy_cord(&gen, &cy, &newnm, p);
	fl = belong_to_cyhead0(gen, cy, p, fl);
	fl = belong_to_cyhead1(gen, cy, p, fl);
	return (fl);
}

int				belong_cy2(t_general gen, t_cylinder cy, t_vector *p)
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
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <=
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 2;
	}
	if (t[1] > 1 && fl > 0 && fl != 2)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <=
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 3;
	}
	return (fl);
}
