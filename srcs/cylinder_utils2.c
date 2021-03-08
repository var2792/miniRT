/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

void	rot_cy_cord(t_general *gen, t_cylinder *cy, t_vector *new, t_vector *p)
{
	t_vector	*mat;
	float		t[3];

	if (!(mat = malloc(sizeof(t_vector) * 4)))
		return ;
	ft_write_xyz(&(mat[0]), new->x, new->y, 0);
	ft_write_xyz(&(mat[1]), cy->nm.x, cy->nm.y, 0);
	t[2] = acos(dot_prv(mat[0], mat[1]) / len_vec(mat[0]) / len_vec(mat[1]));
	ft_write_xyz(&(mat[0]), cos(t[2]), sin(t[2]), 0);
	ft_write_xyz(&(mat[1]), -sin(t[2]), cos(t[2]), 0);
	ft_write_xyz(&(mat[2]), 0, 0, 1);
	ft_write_xyz(&(mat[3]), 0, 0, 0);
	if (!p)
	{
		gen->scene.cdo = mult_m_v(mat, gen->scene.cdo);
		gen->scene.cdv = mult_m_v(mat, gen->scene.cdv);
		cy->cd = mult_m_v(mat, cy->cd);
		ft_write_xyz(&(mat[0]), cy->nm.x, cy->nm.y, cy->nm.z);
		ft_write_xyz(&(cy->nm), new->x, new->y, new->z);
		ft_write_xyz(new, mat[0].x, mat[0].y, mat[0].z);
	}
	else
		*p = mult_m_v(mat, *p);
	free(mat);
}

void	rot_shadow_cy(t_light *num_l, t_cylinder *cy,
t_vector *new, t_vector *pt)
{
	t_vector	*mat;
	float		t[3];

	if (!(mat = malloc(sizeof(t_vector) * 4)))
		return ;
	ft_write_xyz(&(mat[0]), new->x, new->y, 0);
	ft_write_xyz(&(mat[1]), cy->nm.x, cy->nm.y, 0);
	t[2] = acos(dot_prv(mat[0], mat[1]) / len_vec(mat[0]) / len_vec(mat[1]));
	ft_write_xyz(&(mat[0]), cos(t[2]), sin(t[2]), 0);
	ft_write_xyz(&(mat[1]), -sin(t[2]), cos(t[2]), 0);
	ft_write_xyz(&(mat[2]), 0, 0, 1);
	ft_write_xyz(&(mat[3]), 0, 0, 0);
	num_l->cd = mult_m_v(mat, num_l->cd);
	*pt = mult_m_v(mat, *pt);
	cy->cd = mult_m_v(mat, cy->cd);
	ft_write_xyz(&(mat[0]), cy->nm.x, cy->nm.y, cy->nm.z);
	ft_write_xyz(&(cy->nm), new->x, new->y, new->z);
	ft_write_xyz(new, mat[0].x, mat[0].y, mat[0].z);
	free(mat);
}
