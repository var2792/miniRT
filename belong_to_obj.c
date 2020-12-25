#include "belong_to_obj.h"

int check_prew_pix_xy(t_vector check, t_objscene objects, t_canvas scene, t_vector pix, int *i)
{
	if (check.x - scene.coord_v.x < 0.0019 && check.x - scene.coord_v.x > -0.0019 && check.y - scene.coord_v.y < 0.0019 && check.y - scene.coord_v.y > -0.0019)
	{
		(*i)++;
		return (1);
	}
	//printf("%f, %f - %f, %f\n", check.x, check.y ,scene.coord_v.x, scene.coord_v.y);
	return (0);
	(void)objects;
	(void)pix;
	(void)check;
	(void)scene;
}

float		belong_to_sphere(t_objscene objects, t_canvas *scene, t_vector pix, float color, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	t_vector check;

	ft_write_xyz(&check, scene->coord_v.x, scene->coord_v.y, scene->coord_v.z);
	//printf("%f, %f - %f, %f\n", check.x, check.y ,scene->coord_v.x, scene->coord_v.y);
	scene->coord_v.x = (pix.x - objects.r.x / 2) * scene->viewport.x / objects.r.x;
	scene->coord_v.y = (objects.r.y / 2 - pix.y) * scene->viewport.y / objects.r.y;
	scene->coord_v.z = scene->viewport.z;

	scene->coord_v = rotation_multiply(objects, scene->coord_v); // только эта строка отвечает за поворот камеры
	//if (check_prew_pix_xy(check,  objects, *scene, pix, i)) return (color); //проверка на повтор пикселей viewport -- замедляет тк слишком часто true???
	(*i)++;
	k[0] = scalar_product_vecs(scene->coord_v, scene->coord_v);
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, scene->coord_0, -1, objects.sp[(int)pix.z].coord), add_t_vecs( 1, scene->coord_v, -1, scene->coord_0));
	k[2] = scalar_product_vecs(add_t_vecs( 1, scene->coord_0, -1, objects.sp[(int)pix.z].coord), add_t_vecs( 1, scene->coord_0, -1, objects.sp[(int)pix.z].coord)) - objects.sp[(int)pix.z].diam * objects.sp[(int)pix.z].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	//printf("k1 = %f,\tk2 = %f,\tk3 = %f,\tD = %f\n", k[0], k[1], k[2], t[1]);
	if (t[1] < -0.01 || (k[0] == 0 && k[1] == 0))
		return (-5);
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0

	if (t[0] <= 1 && t[1] <= 1)
		return (-5);
	if ((t[0] < 0 || t[1] <= t[0]))
		p = add_t_vecs(1, scene->coord_0, t[1], add_t_vecs( 1, scene->coord_v, -1, scene->coord_0));
	else //if ((t[1] < 1 || t[0] < t[1]))
		p = add_t_vecs(1, scene->coord_0, t[0], add_t_vecs( 1, scene->coord_v, -1, scene->coord_0));

	return (light_change_sp(objects, *scene, p, (int)pix.z));
	(void)color;
	(void)i;
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
