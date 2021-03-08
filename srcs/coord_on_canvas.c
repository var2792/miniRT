/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_on_canvas.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

void		correct_angle(float *t0, float *t1, float *t2, t_vector cam)
{
	if (*t0 > PI - EPS && *t2 > PI - EPS)
	{
		*t0 = 0;
		*t2 = 0;
	}
	if (*t1 > PI - EPS && *t2 > PI - EPS)
		*t1 = 0;
	if (cam.y < 0)
		*t0 *= (-1);
	if (cam.x < 0)
		*t1 *= (-1);
	*t2 = 0;
}

t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord)
{
	t_vector	*mt;
	float		t[3];

	if (!(mt = malloc(sizeof(t_vector) * 4)))
		return (NULL);
	ft_write_xyz(&(mt[0]), 0, cam.y, cam.z);
	ft_write_xyz(&(mt[1]), orig.x, orig.y, orig.z);
	t[0] = (len_vec(mt[0]) < EPS || len_vec(mt[0]) < EPS || len_vec(mt[1]) <
	EPS) ? 0 : acos(dot_prv(mt[0], mt[1]) / len_vec(mt[0]) / len_vec(mt[1]));
	ft_write_xyz(&(mt[0]), cam.x, 0, cam.z);
	ft_write_xyz(&(mt[1]), orig.x, orig.y, orig.z);
	t[1] = (len_vec(mt[0]) < EPS || len_vec(mt[0]) < EPS || len_vec(mt[1])
	< EPS) ? 0 : acos(dot_prv(mt[0], mt[1]) / len_vec(mt[0]) / len_vec(mt[1]));
	t[2] = (cam.z < 0) ? PI : 0;
	correct_angle(&(t[0]), &(t[1]), &(t[2]), cam);
	ft_write_xyz(&(mt[0]), cos(t[1]) * cos(t[2]),
	-sin(t[0]) * sin(t[1]) * cos(t[2]) + cos(t[0]) * sin(t[2]),
	-cos(t[0]) * sin(t[1]) * cos(t[2]) - sin(t[0]) * sin(t[2]));
	ft_write_xyz(&(mt[1]), -cos(t[1]) * sin(t[2]),
	cos(t[0]) * cos(t[2]) + sin(t[0]) * sin(t[1]) * sin(t[2]),
	-sin(t[0]) * cos(t[2]) + cos(t[0]) * sin(t[1]) * sin(t[2]));
	ft_write_xyz(&(mt[2]), sin(t[1]),
	sin(t[0]) * cos(t[1]), cos(t[0]) * cos(t[1]));
	ft_write_xyz(&(mt[3]), coord.x, coord.y, coord.z);
	return (mt);
}

int			parse_put_canvas(t_scene *scene, t_scobjs objs, t_camera *cam)
{
	scene->cdo.x = cam->cd.x;
	scene->cdo.y = cam->cd.y;
	scene->cdo.z = cam->cd.z;
	scene->viewport.x = tan(cam->fov / 2 * PI / 180);
	scene->viewport.y = scene->viewport.x * objs.r.y / objs.r.x;
	scene->viewport.z = 1;
	if (!(scene->rotmat = rotation_matrix(cam->nm, objs.orig_cam, cam->cd)))
		return (errors_mes(7, 0));
	return (0);
}

t_vector	trans_pixv(t_general gen)
{
	gen.scene.cdv.x = (gen.pix.x - gen.objs.r.x / 2) *
	gen.scene.viewport.x / gen.objs.r.x;
	gen.scene.cdv.y = (gen.objs.r.y / 2 - gen.pix.y) *
	gen.scene.viewport.y / gen.objs.r.y;
	gen.scene.cdv.z = gen.scene.viewport.z;
	gen.scene.cdv = mult_m_v(gen.scene.rotmat, gen.scene.cdv);
	return (gen.scene.cdv);
}
