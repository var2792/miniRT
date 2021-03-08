/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_shadow.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		shadow_cyhead0(t_cylinder cy, t_vector pcy, t_light num_l)
{
	t_vector	p;
	t_vector	h;
	float		t1;
	float		t2;

	h = sum_vs(1, cy.cd, -cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t1 = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t2 = dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	t1 = t1 / t2;
	p = sum_vs(1, num_l.cd, t1, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, h)) < cy.d / 2)
		if (len_vec(sum_vs(1, p, -1, num_l.cd)) <
		len_vec(sum_vs(1, pcy, -1, num_l.cd)))
			return (1);
	return (0);
}

int		shadow_cyhead1(t_cylinder cy, t_vector pcy, t_light num_l)
{
	t_vector	p;
	t_vector	h;
	float		t1;
	float		t2;

	h = sum_vs(1, cy.cd, cy.h / 2 / sqrt(dot_prv(cy.nm, cy.nm)), cy.nm);
	t1 = dot_prv(cy.nm, h) - dot_prv(cy.nm, num_l.cd);
	t2 = dot_prv(cy.nm, pcy) - dot_prv(cy.nm, num_l.cd);
	t1 = t1 / t2;
	p = sum_vs(1, num_l.cd, t1, sum_vs(1, pcy, -1, num_l.cd));
	if (len_vec(sum_vs(1, p, -1, h)) < cy.d / 2)
		if (len_vec(sum_vs(1, p, -1, num_l.cd)) <
		len_vec(sum_vs(1, pcy, -1, num_l.cd)))
			return (1);
	return (0);
}

int		shadow_cy(t_cylinder cy, t_light num_l, t_vector pt)
{
	float		t[2];
	t_vector	p;

	p = sum_vs(1, pt, -1, num_l.cd);
	if ((t[1] = find_discr(cross_prv(p, cy.nm), sum_vs(1, cross_prv(num_l.cd,
	cy.nm), -1, cross_prv(cy.cd, cy.nm)),
	dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]))) > EPS)
	{
		if ((t[0] > EPS && t[0] < 1 - EPS) || (t[1] < 1 - EPS))
		{
			p = sum_vs(1, num_l.cd, (t[0] > EPS && t[0] < 1 - EPS) ?
			t[0] : t[1], sum_vs(1, pt, -1, num_l.cd));
			if (len_vec(sum_vs(1, p, -1, cy.cd)) <
			sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
				return (1);
		}
	}
	return (0);
}

float	check_shadow_cy(t_light num_l, int num_cy,
t_scobjs objects, t_vector pt)
{
	int			i;
	t_list		*temp;
	t_cylinder	*cy;

	temp = objects.cy;
	i = 0;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			if (shadow_cy(*cy, num_l, pt))
				return (0);
			if (shadow_cyhead0(*cy, pt, num_l) ||
			shadow_cyhead1(*cy, pt, num_l))
				return (0);
		}
		temp = temp->next;
		i++;
	}
	return (1);
}
