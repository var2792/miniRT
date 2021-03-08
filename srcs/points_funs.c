/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_funs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

t_vector	find_apex_sq(t_square sq, t_vector *rotmat, t_vector p)
{
	t_vector	tp;
	float		t;

	tp = mult_m_v(rotmat, p);
	t = sqrt(sq.s * sq.s / 2 / dot_prv(tp, tp));
	tp = sum_vs(1, sq.cd, t, tp);
	return (tp);
}

void		find_point_sq(t_square sq, t_vector (*p)[])
{
	t_vector	pnul;
	t_vector	temp;
	t_vector	*rotmat;

	ft_write_xyz(&pnul, 0, 0, 0);
	ft_write_xyz(&temp, 0, 0, 1);
	rotmat = rotation_matrix(sq.nm, temp, pnul);
	ft_write_xyz(&pnul, 1, 1, 0);
	(*p)[0] = find_apex_sq(sq, rotmat, pnul);
	ft_write_xyz(&pnul, -1, 1, 0);
	(*p)[1] = find_apex_sq(sq, rotmat, pnul);
	ft_write_xyz(&pnul, 1, -1, 0);
	(*p)[2] = find_apex_sq(sq, rotmat, pnul);
	ft_write_xyz(&pnul, -1, -1, 0);
	(*p)[3] = find_apex_sq(sq, rotmat, pnul);
	free(rotmat);
}

int			point_in_square(t_square sq, t_vector p)
{
	float	x;
	float	y;

	x = dot_prv(sum_vs(1, p, -1, sq.ps[0]),
	sum_vs(1, sq.ps[1], -1, sq.ps[0])) / dot_prv(sum_vs(1, sq.ps[1], -1,
	sq.ps[0]), sum_vs(1, sq.ps[1], -1, sq.ps[0]));
	y = dot_prv(sum_vs(1, p, -1, sq.ps[0]),
	sum_vs(1, sq.ps[2], -1, sq.ps[0])) / dot_prv(sum_vs(1, sq.ps[2], -1,
	sq.ps[0]), sum_vs(1, sq.ps[2], -1, sq.ps[0]));
	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}

int			point_in_triangle(t_triangle tr, t_vector p)
{
	float x;
	float y;

	x = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd2, -1, tr.cd1)) * dot_prv(sum_vs(1, tr.cd3, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)));
	y = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1),
	sum_vs(1, tr.cd2, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd2, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1))) / x;
	x = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd3, -1, tr.cd1),
	sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1),
	sum_vs(1, tr.cd2, -1, tr.cd1))) / x;
	if (x >= 0 && y >= 0 && x + y <= 1)
		return (1);
	return (0);
}
