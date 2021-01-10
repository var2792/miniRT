#include "parse_put_canvas.h"

t_vector	*rotation_matrix(t_objscene objects)
{
	t_vector *mat;
	float T[3];

	mat = malloc(sizeof(t_vector) * 4);
	ft_write_xyz(&(mat[0]), 0, objects.c[0].normal.y, objects.c[0].normal.z);
	T[0] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam));
	ft_write_xyz(&(mat[0]), objects.c[0].normal.x, 0, objects.c[0].normal.z);
	T[1] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam));
	//ft_write_xyz(&(mat[0]), objects.c[0].normal.x, objects.c[0].normal.y, objects.c[0].normal.z);
	T[2] = (objects.c[0].normal.z < 0) ? 3.1415928 : 0;//(!(objects.c[0].normal.z < 0) || (lenght_vecs(mat[0]) < 0.01)) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam));
	if (T[0] > 3.14 && T[2] > 3.14)
	{
		T[0] = 0;
		T[2] = 0;
	}
	if (objects.c[0].normal.y < 0)
		T[0] *= (-1);
	if (objects.c[0].normal.x < 0)
		T[1] *= (-1);
	//if (vec.x < 0.00000001 && vec.x > -0.00000001 && vec.y < 0.00000001 && vec.y > -0.00000001)
		printf("T[0] = %f, T[1] = %f, T[2]= %f\n", T[0] * 180 / 3.1415925, T[1] * 180 / 3.1415925, T[2] * 180 / 3.1415925);

	ft_write_xyz(&(mat[0]), cos(T[1]) * cos(T[2]), -cos(T[1]) * sin(T[2]), sin(T[1]));
	ft_write_xyz(&(mat[1]), -sin(T[0]) * cos(T[2]) * sin(T[1]) + cos(T[0]) * sin(T[2]), cos(T[0]) * cos(T[2]) + sin(T[0]) * sin(T[1]) * sin(T[2]), -cos(T[1]) * sin(T[0]));
	ft_write_xyz(&(mat[2]), cos(T[0]) * cos(T[2]) * sin(T[1]) + sin(T[0]) * sin(T[2]), sin(T[0]) * cos(T[2]) - cos(T[0]) * sin(T[1]) * sin(T[2]), cos(T[1]) * cos(T[0]));

	//ft_write_xyz(&(mat[3]), objects.c[0].coord.x, objects.c[0].coord.y, objects.c[0].coord.z);
	ft_write_xyz(&(mat[3]), objects.c[0].coord.x, objects.c[0].coord.y/* * tan(objects.c[0].fov / 2 * 3.1415926 / 180)*/, objects.c[0].coord.z);
	
	return (mat);
}

t_canvas	parse_put_canvas(t_general gen)
{
	t_canvas scene;

	scene.coord_0.x = gen.objects.c[0].coord.x;
	scene.coord_0.y = gen.objects.c[0].coord.y;
	scene.coord_0.z = gen.objects.c[0].coord.z;
	scene.viewport.x = tan(gen.objects.c[gen.num_cam].fov / 2 * 3.1415926 / 180);//1;
	scene.viewport.y = scene.viewport.x * gen.objects.r.y / gen.objects.r.x;
	scene.viewport.z = 1;//(scene.viewport.x / tan(objects.c[0].fov / 2 * 3.1415926 / 180));
	//printf("vx = %f, vy = %f, vz = %f\n", scene->viewport.x, scene->viewport.y, scene->viewport.z);
	scene.rotmat = rotation_matrix(gen.objects);
	return (scene);
}

