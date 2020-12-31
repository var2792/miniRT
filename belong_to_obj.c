#include "belong_to_obj.h"

int		check_prew_pix_xy(t_vector check, t_objscene objects, t_canvas scene, t_vector pix, int *i)
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

int		check_see_sp(t_general gen, float t[], int num_sp)
{
	float k[3];
	float t_n[2];
	int i;

	i = 0;
	if (t[0] > t[1])
		t[0] = t[1];
	while (gen.objects.sp[i].is)
	{
		if (i != num_sp)
		{
			k[0] = scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0), add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0), -1, gen.scene.coord_0));
			k[2] = scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord)) - gen.objects.sp[i].diam * gen.objects.sp[i].diam / 4;
			t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t_n[1] < -0.01 || (k[0] == 0 && k[1] == 0)))
			{
				t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
				t_n[1] = (t_n[0] < 1 && t_n[1] < 0.01 && t_n[1] > -0.01) ? -5 : (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
				if ((t_n[0] >= 1 && t_n[0] < t[0]) || (t_n[1] >= 1 && t_n[1] < t[0]))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

float	belong_to_sphere(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	t_vector check;

	ft_write_xyz(&check, 0, 0, 0);
	//printf("%f, %f - %f, %f\n", check.x, check.y ,scene->coord_v.x, scene->coord_v.y);
	gen->scene.coord_v.x = (gen->pix.x - gen->objects.r.x / 2) * gen->scene.viewport.x / gen->objects.r.x + gen->objects.c[0].coord.x / 9;
	gen->scene.coord_v.y = (gen->objects.r.y / 2 - gen->pix.y) * gen->scene.viewport.y / gen->objects.r.y + gen->objects.c[0].coord.y / 9;
	gen->scene.coord_v.z = gen->scene.viewport.z + gen->objects.c[0].coord.z / 9;

	gen->scene.coord_v = rotation_multiply(gen->objects, gen->scene.coord_v); // только эта строка отвечает за поворот камеры
	//if (check_prew_pix_xy(check,  objects, *scene, pix, i)) return (color); //проверка на повтор пикселей viewport -- замедляет тк слишком часто true???
	(*i)++;
	k[0] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0), add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0), -1, gen->scene.coord_0));
	k[2] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord)) - gen->objects.sp[(int)gen->pix.z].diam * gen->objects.sp[(int)gen->pix.z].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	//printf("k1 = %f,\tk2 = %f,\tk3 = %f,\tD = %f\n", k[0], k[1], k[2], t[1]);
	if (t[1] < -0.01 || (k[0] == 0 && k[1] == 0))
		return (-5);
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
	if (check_see_sp(*gen, t, (int)gen->pix.z))
		return (-5);
	if (t[0] <= 1 && t[1] <= 1)
		return (-5);
	if ((t[0] < 0 || t[1] <= t[0]))
		p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	else //if ((t[1] < 1 || t[0] < t[1]))
		p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));

	return (light_change_sp(*gen, p, (int)gen->pix.z));
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
