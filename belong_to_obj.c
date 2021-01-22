#include "belong_to_obj.h"

float	belong_to_sphere(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	fl = 1;
	gen->scene.coord_v.x = (gen->pix.x - gen->objects.r.x / 2) * gen->scene.viewport.x / gen->objects.r.x;
	gen->scene.coord_v.y = (gen->objects.r.y / 2 - gen->pix.y) * gen->scene.viewport.y / gen->objects.r.y;
	gen->scene.coord_v.z = gen->scene.viewport.z;

	gen->scene.coord_v = multiply_mat_vec(gen->scene.rotmat, gen->scene.coord_v); //только эта строка отвечает за поворот камеры
	/*if (gen->pix.x == 0 && gen->pix.y == 0)
		printf(" 0   0  %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 0 && gen->pix.y == 512)
		printf(" 0  512 %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 512 && gen->pix.y == 0)
		printf("512  0  %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 512 && gen->pix.y == 512)
		printf("512 512 %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);*/
		
	(*i)++;
	k[0] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0), add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	k[2] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord)) - gen->objects.sp[(int)gen->pix.z].diam * gen->objects.sp[(int)gen->pix.z].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		fl = 0;
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
	if ((t[0] < 0 || t[1] <= t[0]))
		p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	else //if ((t[1] < 1 || t[0] < t[1]))
		p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	
	if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
		fl = 0;
	
	/*(fl == 1 && z == 0) fun;
	(fl == 1 && z != 0) fun;
	(fl == 0 && z == 0) -5;
	(fl == 0 && z != 0) color;*/
	gen->color = (fl == 1) ? light_change_sp(*gen, p, (int)gen->pix.z) : gen->color;
	gen->pix.z += 1;
	if (gen->objects.sp[(int)gen->pix.z].is == 1)
		gen->color = belong_to_sphere(gen, i);
	return (gen->color);
	(void)i;
}

int		belong_to_plane(t_general *gen, int *i)
{
	t_vector p;
	float t, t1, t2;

	gen->scene.coord_v.x = (gen->pix.x - gen->objects.r.x / 2) * gen->scene.viewport.x / gen->objects.r.x;
	gen->scene.coord_v.y = (gen->objects.r.y / 2 - gen->pix.y) * gen->scene.viewport.y / gen->objects.r.y;
	gen->scene.coord_v.z = gen->scene.viewport.z;

	gen->scene.coord_v = multiply_mat_vec(gen->scene.rotmat, gen->scene.coord_v);
	(*i)++;
	
	t1 = scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.pl[(int)gen->pix.z].coord) - scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t2 = scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->scene.coord_v) - scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t = t1 / t2;
	//printf("PL %f\n", t);
	ft_write_xyz(&p, 0, 0, 0);
	p = add_t_vecs(1, p, t, add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	
	if (!check_see_objs(*gen, p, 100 + (int)gen->pix.z) && (t > 1 && t < 200))
		gen->color = light_change_pl(*gen, p, (int)gen->pix.z);

	gen->pix.z += 1;
	if (gen->objects.pl[(int)gen->pix.z].is == 1)
		gen->color = belong_to_plane(gen, i);
	return (gen->color);
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
