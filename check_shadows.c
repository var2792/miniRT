#include "check_shadows.h"

float		check_shadow(int num_l, int num_ob, t_objscene objects, t_vector p)
{
	float res, temp;

	res = 1;
	if (num_ob > -1 && num_ob < 100) //sphere
		res = check_shadow_sp(num_l, num_ob, objects, p);
	else
		res = check_shadow_sp(num_l, -1, objects, p);

	if (num_ob > 99 && num_ob < 200) //plane
		res = ((temp = check_shadow_pl(num_l, (int)(num_ob - 100), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_pl(num_l, -1, objects, p)) < res ) ? temp : res;

	if (num_ob > 199 && num_ob < 300) //square
		res = ((temp = check_shadow_sq(num_l, (int)(num_ob - 200), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_sq(num_l, -1, objects, p)) < res ) ? temp : res;

	if (num_ob > 299 && num_ob < 400) //triangle
		res = ((temp = check_shadow_tr(num_l, (int)(num_ob - 300), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_tr(num_l, -1, objects, p)) < res ) ? temp : res;
/*
	if (num_ob > 399 && num_ob < 500) //cylinder
		res = ((temp = check_shadow_cy(num_l, (int)(num_ob - 400), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_cy(num_l, -1, objects, p)) < res ) ? temp : res;
*/

	return (res);
}

float		check_shadow_sp(int num_l, int num_sp, t_objscene objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;

	i = 0;
	while (objects.sp[i].is)
	{
		if (i != num_sp)
		{
			k[0] = scalar_product_vecs(add_t_vecs(1, p, -1, objects.l[num_l].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			k[1] = 2 * scalar_product_vecs(add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			k[2] = scalar_product_vecs(add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord)) - objects.sp[i].diam * objects.sp[i].diam / 4;
			t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
			{
				t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
				t_n[1] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
				if ((t_n[0] > 0 && t_n[0] < 1) || (t_n[1] > 0 && t_n[1] < 1))
					return (0);
			}
		}
		i++;
	}
	return (1);
}

int		check_orient(int num_l, int num_pl, t_general gen, t_vector p)
{

	return (1);
	(void)num_l;
	(void)num_pl;
	(void)gen;
	(void)p;
}

float		check_shadow_pl(int num_l, int num_pl, t_objscene objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2, t;
	int i;

	i = 0;
	while (objects.pl[i].is)
	{
		if (i != num_pl)
		{
			t1 = scalar_product_vecs(objects.pl[i].normal, objects.pl[i].coord) - scalar_product_vecs(objects.pl[i].normal, objects.l[num_l].coord);
			t2 = scalar_product_vecs(objects.pl[i].normal, p) - scalar_product_vecs(objects.pl[i].normal, objects.l[num_l].coord);
			t = t1 / t2;
			if (t >= 0 && t <= 1)
				return (0);
		}
		i++;
	}
	return (1);
}

float		check_shadow_sq(int num_l, int num_sq, t_objscene objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2;
	int i;
	t_vector t;

	i = 0;
	while (objects.sq[i].is)
	{
		if (i != num_sq)
		{
			t1 = scalar_product_vecs(objects.sq[i].normal, objects.sq[i].coord) - scalar_product_vecs(objects.sq[i].normal, objects.l[num_l].coord);
			t2 = scalar_product_vecs(objects.sq[i].normal, p) - scalar_product_vecs(objects.sq[i].normal, objects.l[num_l].coord);
			t1 = t1 / t2;
			t = add_t_vecs(1, objects.l[num_l].coord, t1, add_t_vecs( 1, p, -1, objects.l[num_l].coord));

			if (point_in_square(objects.sq[i], t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		i++;
	}
	return (1);
}

float		check_shadow_tr(int num_l, int num_tr, t_objscene objects, t_vector p)
{
	float t1, t2;
	int i;
	t_vector t;

	i = 0;
	while (objects.tr[i].is)
	{
		if (i != num_tr)
		{
			t1 = scalar_product_vecs(objects.tr[i].normal, objects.tr[i].coord_fir) - scalar_product_vecs(objects.tr[i].normal, objects.l[num_l].coord);
			t2 = scalar_product_vecs(objects.tr[i].normal, p) - scalar_product_vecs(objects.tr[i].normal, objects.l[num_l].coord);
			t1 = t1 / t2;
			t = add_t_vecs(1, objects.l[num_l].coord, t1, add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			if (point_in_triangle(objects.tr[i], t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		i++;
	}
	return (1);
}
