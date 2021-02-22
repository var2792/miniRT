#include "../incs/funct_def.h"

void		correct_angle(float *T0, float *T1, float *T2, t_vector cam)
{
	if (*T0 > 3.14 && *T2 > 3.14)
	{
		*T0 = 0;
		*T2 = 0;
	}
	if (*T1 > 3.14 && *T2 > 3.14)
		*T1 = 0;
	if (cam.y < 0)
		*T0 *= (-1);
	if (cam.x < 0)
		*T1 *= (-1);
	*T2 = 0;
}

t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord)
{
	t_vector *mat;
	float T[3];

	if (!(mat = malloc(sizeof(t_vector) * 4)))
		return (NULL);
	ft_write_xyz(&(mat[0]), 0, cam.y, cam.z);
	T[0] = (len_vec(mat[0]) < 0.001) ? 0 : acos(dot_prv(mat[0], orig) / len_vec(mat[0]) / len_vec(orig));
	ft_write_xyz(&(mat[0]), cam.x, 0, cam.z);
	T[1] = (len_vec(mat[0]) < 0.001) ? 0 : acos(dot_prv(mat[0], orig) / len_vec(mat[0]) / len_vec(orig));
	T[2] = (cam.z < 0) ? 3.1415928 : 0;
	correct_angle(&(T[0]), &(T[1]), &(T[2]), cam);
	//printf("T[0] = %f, T[1] = %f, T[2]= %f\n", T[0] * 180 / 3.1415925, T[1] * 180 / 3.1415925, T[2] * 180 / 3.1415925);
/*
	if (T[0] > 0.001 || T[0] < -0.001)
	{
		ft_write_xyz(&(mat[0]), 1, 0, 0);
		ft_write_xyz(&(mat[1]), 0, cos(T[0]), -sin(T[0]));
		ft_write_xyz(&(mat[2]), 0, sin(T[0]), cos(T[0]));
	}
	if (T[1] > 0.001 || T[1] < -0.001)
	{
		ft_write_xyz(&(mat[0]), cos(T[1]), 0, -sin(T[1]));
		ft_write_xyz(&(mat[1]), 0, 1, 0);
		ft_write_xyz(&(mat[2]), sin(T[1]), 0, cos(T[1]));
	}
	ft_write_xyz(&(mat[0]), cos(T[2]), sin(T[2]), 0);
	ft_write_xyz(&(mat[1]), -sin(T[2]), cos(T[2]), 0);
	ft_write_xyz(&(mat[2]), 0, 0, 1);
*/
	ft_write_xyz(&(mat[0]), cos(T[1]) * cos(T[2]), - sin(T[0]) * sin(T[1]) * cos(T[2]) + cos(T[0]) * sin(T[2]), - cos(T[0]) * sin(T[1]) * cos(T[2]) - sin(T[0]) * sin(T[2]));
	ft_write_xyz(&(mat[1]), - cos(T[1]) * sin(T[2]), cos(T[0]) * cos(T[2]) + sin(T[0]) * sin(T[1]) * sin(T[2]), - sin(T[0]) * cos(T[2]) + cos(T[0]) * sin(T[1]) * sin(T[2]));
	ft_write_xyz(&(mat[2]), sin(T[1]), sin(T[0]) * cos(T[1]), cos(T[0]) * cos(T[1]));
	ft_write_xyz(&(mat[3]), coord.x, coord.y, coord.z);
	return (mat);
}

int	parse_put_canvas(t_scene *scene, t_scobjs objs, t_camera *cam) //(t_general gen) //
{
	scene->cdo.x = cam->cd.x;
	scene->cdo.y = cam->cd.y;
	scene->cdo.z = cam->cd.z;
	scene->viewport.x = tan(cam->fov / 2 * 3.1415926 / 180);//1;
	scene->viewport.y = scene->viewport.x * objs.r.y / objs.r.x;
	scene->viewport.z = 1;//(scene->viewport.x / tan(objects.c[0].fov / 2 * 3.1415926 / 180));
	//printf("vx = %f, vy = %f, vz = %f\n", scene->viewport.x, scene->viewport.y, scene->viewport.z);
	if (!(scene->rotmat = rotation_matrix(cam->nm, objs.orig_cam, cam->cd)))
		return (errors_mes(7,0));
	return (0);
}

t_vector	trans_pixv(t_general gen)
{
	gen.scene.cdv.x = (gen.pix.x - gen.objs.r.x / 2) * gen.scene.viewport.x / gen.objs.r.x;
	gen.scene.cdv.y = (gen.objs.r.y / 2 - gen.pix.y) * gen.scene.viewport.y / gen.objs.r.y;
	gen.scene.cdv.z = gen.scene.viewport.z;
	gen.scene.cdv = mult_m_v(gen.scene.rotmat, gen.scene.cdv); //только эта строка отвечает за поворот камеры
	return (gen.scene.cdv);
}
