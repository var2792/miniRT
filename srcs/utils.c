/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

t_vector		ft_write_xyz(t_vector *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (*vec);
}

unsigned int	ft_colorvec_unsint(float br, t_vector vec)
{
	unsigned int num;
	unsigned int r[2];
	unsigned int g[2];
	unsigned int b[2];

	r[0] = (unsigned int)(vec.x) / 16;
	r[1] = (unsigned int)(vec.x) % 16;
	g[0] = (unsigned int)(vec.y) / 16;
	g[1] = (unsigned int)(vec.y) % 16;
	b[0] = (unsigned int)(vec.z) / 16;
	b[1] = (unsigned int)(vec.z) % 16;
	num = (r[0] * 16 + r[1]) * 16 * 16 * 16 * 16
	+ (g[0] * 16 + g[1]) * 16 * 16 + b[0] * 16 + b[1];
	return (br * num);
}

unsigned int	rescolcy(t_vector cycl, t_vector sum, t_vector acl, float br)
{
	t_vector cl;

	br = (br > 1) ? 1 : br;
	cl = sum_vs(br, sum_vs(0.4, cycl, 0.4, sum), 0.2 * br, acl);
	correct_color(&(cl));
	return (ft_colorvec_unsint(1, cl));
}
