#include "parse_put_canvas.h"

t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord)//t_objscene objects)
{
	t_vector *mat;
	float T[3];

	mat = malloc(sizeof(t_vector) * 4);
	ft_write_xyz(&(mat[0]), 0, cam.y, cam.z);
	T[0] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], orig) / lenght_vecs(mat[0]) / lenght_vecs(orig));
	ft_write_xyz(&(mat[0]), cam.x, 0, cam.z);
	T[1] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], orig) / lenght_vecs(mat[0]) / lenght_vecs(orig));
	T[2] = (cam.z < 0) ? 3.1415928 : 0;
	if (T[0] > 3.14 && T[2] > 3.14)
	{
		T[0] = 0;
		T[2] = 0;
	}
	if (T[1] > 3.14 && T[2] > 3.14)
		T[1] = 0;
	if (cam.y < 0)
		T[0] *= (-1);
	if (cam.x < 0)
		T[1] *= (-1);
	T[2] = 0;
	//T[0] = 0; T[1] = 0; T[2] = 3.1415925;

	//printf("T[0] = %f, T[1] = %f, T[2]= %f\n", T[0] * 180 / 3.1415925, T[1] * 180 / 3.1415925, T[2] * 180 / 3.1415925);

/*   	if (T[0] > 0.001 || T[0] < -0.001)
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

t_scene	parse_put_canvas(t_general gen)
{
	t_scene scene;

	scene.coord_0.x = gen.objects.c[gen.num_cam].coord.x;
	scene.coord_0.y = gen.objects.c[gen.num_cam].coord.y;
	scene.coord_0.z = gen.objects.c[gen.num_cam].coord.z;
	scene.viewport.x = tan(gen.objects.c[gen.num_cam].fov / 2 * 3.1415926 / 180);//1;
	scene.viewport.y = scene.viewport.x * gen.objects.r.y / gen.objects.r.x;
	scene.viewport.z = 1;//(scene.viewport.x / tan(objects.c[0].fov / 2 * 3.1415926 / 180));
	//printf("vx = %f, vy = %f, vz = %f\n", scene->viewport.x, scene->viewport.y, scene->viewport.z);
	scene.rotmat = rotation_matrix(gen.objects.c[gen.num_cam].normal, gen.objects.orig_cam, gen.objects.c[gen.num_cam].coord);
	return (scene);
}

t_vector	trans_pix_v(t_general gen)
{
	gen.scene.coord_v.x = (gen.pix.x - gen.objects.r.x / 2) * gen.scene.viewport.x / gen.objects.r.x;
	gen.scene.coord_v.y = (gen.objects.r.y / 2 - gen.pix.y) * gen.scene.viewport.y / gen.objects.r.y;
	gen.scene.coord_v.z = gen.scene.viewport.z;

	gen.scene.coord_v = multiply_mat_vec(gen.scene.rotmat, gen.scene.coord_v);  //только эта строка отвечает за поворот камеры
	return (gen.scene.coord_v);
}
