/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_see.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		see_cy2(t_general gen, t_cylinder cy, t_vector *p)
{
	float		t[2];
	int			fl;

	*p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
	t[1] = find_discr(cross_prv(*p, cy.nm), sum_vs(1, cross_prv(gen.scene.cdo,
	cy.nm), -1, cross_prv(cy.cd, cy.nm)),
	dot_prv(cy.nm, cy.nm) * cy.d * cy.d / 4, &(t[0]));
	fl = t[1] < EPS ? 0 : 1;
	if (t[0] > EPS && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[0],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 2;
	}
	if (t[1] > EPS && fl != 2 && fl > 0)
	{
		*p = sum_vs(1, gen.scene.cdo, t[1],
		sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
		if (len_vec(sum_vs(1, *p, -1, cy.cd)) <
		sqrt(cy.h * cy.h / 4 + cy.d * cy.d / 4))
			fl = 3;
	}
	return (fl);
}

int		see_cy(t_general gen, t_cylinder cy, t_vector *p)
{
	int			fl;

	fl = see_cy2(gen, cy, p);
	fl = belong_to_cyhead0(gen, cy, p, fl);
	fl = belong_to_cyhead1(gen, cy, p, fl);
	return (fl);
}

int		check_see_cy(t_general gen, t_vector ptr, int num_cy)
{
	int			i;
	int			fl;
	t_vector	p;
	t_list		*temp;
	t_cylinder	*cy;

	i = 0;
	temp = gen.objs.cy;
	while (temp)
	{
		if (i != num_cy)
		{
			cy = temp->content;
			fl = see_cy(gen, *cy, &p);
			if (fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <
			len_vec(sum_vs(1, ptr, -1, gen.scene.cdo)))
				return (1);
		}
		temp = temp->next;
		i++;
	}
	return (0);
}
