#include "belong_to_obj.h"

float		belong_to_sphere(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];
	t_vector p;

	scene.coord_v.x = (pix.x - objects.r.x / 2) * scene.viewport.x / objects.r.x;
	scene.coord_v.y = (objects.r.y / 2 - pix.y) * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;

	scene.coord_v = rotation_multiply(objects, scene.coord_v);
	k[0] = scalar_product_vecs(scene.coord_v, scene.coord_v);
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, scene.coord_0, -1, objects.sp[(int)pix.z].coord), add_t_vecs( 1, scene.coord_v, -1, scene.coord_0));
	k[2] = scalar_product_vecs(add_t_vecs( 1, scene.coord_0, -1, objects.sp[(int)pix.z].coord), add_t_vecs( 1, scene.coord_0, -1, objects.sp[(int)pix.z].coord)) - objects.sp[(int)pix.z].diam * objects.sp[(int)pix.z].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	//printf("k1 = %f, k2 = %f, k3 = %f, D = %f\n", k[0], k[1], k[2], t[1]);
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (-5);
	if ((int)round(t[1]*10) == 0)
	{
		t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
		if (t[0] < 1)
			return (-5);
	}
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (-k[1] - sqrt(t[1]))/ 2 / k[0];

	if (t[0] <= 1 && t[1] <= 1)
		return (-5);
	if ((t[0] < 0 || t[1] <= t[0]))
		p = add_t_vecs(1, scene.coord_0, t[1], add_t_vecs( 1, scene.coord_v, -1, scene.coord_0));
	else //if ((t[1] < 1 || t[0] < t[1]))
		p = add_t_vecs(1, scene.coord_0, t[0], add_t_vecs( 1, scene.coord_v, -1, scene.coord_0));

	return (light_change_sp(objects, p, (int)pix.z));
}

int		belong_to_plane(t_objscene objects, t_canvas scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}

int		belong_to_square(t_objscene objects, t_canvas scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}

int		belong_to_cylinder(t_objscene objects, t_canvas scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}

int		belong_to_triangle(t_objscene objects, t_canvas scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}
