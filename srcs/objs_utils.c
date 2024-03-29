/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

float	find_discr(t_vector vec1, t_vector vec2, float last, float *t1)
{
	float	k[3];
	float	t2;
	float	dis;

	k[0] = dot_prv(vec1, vec1);
	k[1] = 2 * dot_prv(vec2, vec1);
	k[2] = dot_prv(vec2, vec2) - last;
	dis = k[1] * k[1] - 4 * k[0] * k[2];
	if (dis >= 0 && !(k[0] == 0 && k[1] == 0))
	{
		*t1 = (-k[1] + sqrt(dis)) / 2 / k[0];
		t2 = (-k[1] - sqrt(dis)) / 2 / k[0];
		if (*t1 > t2)
		{
			k[2] = *t1;
			*t1 = t2;
			t2 = k[2];
		}
	}
	else
	{
		t2 = -5;
		*t1 = -5;
	}
	return (t2);
}

float	check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p)
{
	float		alfa;
	t_vector	t;

	t = sum_vs(1, p, -1, cor_0);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		normal = sum_vs(0, t, -1, normal);
	t = sum_vs(1, p, -1, l);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		return (0);
	return (1);
}

float	perpend_to_plane(t_vector cd, t_vector nm, t_vector lig)
{
	t_vector	p;
	float		t;

	t = dot_prv(nm, lig) - dot_prv(nm, cd);
	t /= dot_prv(nm, nm);
	p = sum_vs(1, lig, t, nm);
	return (len_vec(sum_vs(1, p, -1, lig)));
}
