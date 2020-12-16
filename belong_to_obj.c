#include "belong_to_obj.h"

float		belong_to_sphere(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	scene.coord_v.x = (pix.x - objects.r.x / 2) * scene.viewport.x / objects.r.x;
	scene.coord_v.y = (objects.r.y / 2 - pix.y) * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;
	//printf("cx = %f, cy = %f\n", pix.x, pix.y);
	/*printf("vx = %f, vy = %f\n", scene.coord_v.x, scene.coord_v.y);
	printf("Ox = %f, Oy = %f\n", scene.coord_0.x, scene.coord_0.y);
	printf("spx = %f, spy = %f, spz = %f\n", objects.sp.coord.x, objects.sp.coord.y, objects.sp.coord.z);*/

	k[0] = scalar_product_vecs(raz_vecs(scene.coord_v, scene.coord_0), raz_vecs(scene.coord_v, scene.coord_0));
	k[1] = 2 * scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_v, scene.coord_0));
	/*t_vector raz1 = raz_vecs(scene.coord_0, objects.sp.coord);
	printf("---> razx = %f, razy = %f, razz = %f\n", raz1.x, raz1.y, raz1.z);
	t_vector raz2 = raz_vecs(scene.coord_v, scene.coord_0);
	printf("---> razx = %f, razy = %f, razz = %f\n", raz2.x, raz2.y, raz2.z);*/
	k[2] = scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_0, objects.sp.coord)) - objects.sp.diam * objects.sp.diam / 4;
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
	fl = 0;
	if ((t[0] < 0 || t[1] <= t[0]) && !fl)
	{
		p = add_t_vecs(1, scene.coord_0, t[1], raz_vecs(scene.coord_v, scene.coord_0));
		fl = 1;
	}
	if ((t[1] < 1 || t[0] < t[1]) && !fl)
	{
		p = add_t_vecs(1, scene.coord_0, t[0], raz_vecs(scene.coord_v, scene.coord_0));
		fl = 1;
	}
	return (light_change(objects, p, fl));
	//return (-1);
}

int		belong_to_plane(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];

	scene.coord_v.x = pix.x * scene.viewport.x / objects.r.x;
	scene.coord_v.y = pix.y * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;

	k[0] = scalar_product_vecs(raz_vecs(scene.coord_v, scene.coord_0), raz_vecs(scene.coord_v, scene.coord_0));
	k[1] = 2 * scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_v, scene.coord_0));
	k[2] = scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_0, objects.sp.coord)) - objects.sp.diam * objects.sp.diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (0);
	return (1);
}

int		belong_to_square(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];

	scene.coord_v.x = pix.x * scene.viewport.x / objects.r.x;
	scene.coord_v.y = pix.y * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;

	k[0] = scalar_product_vecs(raz_vecs(scene.coord_v, scene.coord_0), raz_vecs(scene.coord_v, scene.coord_0));
	k[1] = 2 * scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_v, scene.coord_0));
	k[2] = scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_0, objects.sp.coord)) - objects.sp.diam * objects.sp.diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (0);
	return (1);
}

int		belong_to_cylinder(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];

	scene.coord_v.x = pix.x * scene.viewport.x / objects.r.x;
	scene.coord_v.y = pix.y * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;

	k[0] = scalar_product_vecs(raz_vecs(scene.coord_v, scene.coord_0), raz_vecs(scene.coord_v, scene.coord_0));
	k[1] = 2 * scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_v, scene.coord_0));
	k[2] = scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_0, objects.sp.coord)) - objects.sp.diam * objects.sp.diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (0);
	return (1);
}

int		belong_to_triangle(t_objscene objects, t_canvas scene, t_vector pix)
{
	float k[3];
	float t[2];

	scene.coord_v.x = pix.x * scene.viewport.x / objects.r.x;
	scene.coord_v.y = pix.y * scene.viewport.y / objects.r.y;
	scene.coord_v.z = scene.viewport.z;

	k[0] = scalar_product_vecs(raz_vecs(scene.coord_v, scene.coord_0), raz_vecs(scene.coord_v, scene.coord_0));
	k[1] = 2 * scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_v, scene.coord_0));
	k[2] = scalar_product_vecs(raz_vecs(scene.coord_0, objects.sp.coord), raz_vecs(scene.coord_0, objects.sp.coord)) - objects.sp.diam * objects.sp.diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (0);
	return (1);
}
