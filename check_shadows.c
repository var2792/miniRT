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

	if (num_ob > 399 && num_ob < 500) //cylinder
		res = ((temp = check_shadow_cy(num_l, (int)(num_ob - 400), objects, p)) < res ) ? temp : res;
	else
		res = ((temp = check_shadow_cy(num_l, -1, objects, p)) < res ) ? temp : res;


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
			k[0] = lenght_vecs(vec_product_vecs(add_t_vecs(1, objects.sp[i].coord, -1, objects.l[num_l].coord), add_t_vecs(1, p, -1, objects.l[num_l].coord))) / lenght_vecs(add_t_vecs(1, p, -1, objects.l[num_l].coord));
			if (k[0] <= objects.sp[i].diam * 2)
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

int		shadow_cyhead0(t_objscene objects, int i, t_vector pcy, int num_l)
{
	t_vector p, h;
	float t1, t2;

	h = add_t_vecs(1, objects.cy[i].coord, - objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(objects.cy[i].normal, objects.cy[i].normal)), objects.cy[i].normal);
	//h = add_t_vecs(1, objects.cy[i].coord, objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(objects.cy[i].normal, objects.cy[i].normal)), objects.cy[i].normal);

	t1 = scalar_product_vecs(objects.cy[i].normal, h) - scalar_product_vecs(objects.cy[i].normal, objects.l[num_l].coord);
	t2 = scalar_product_vecs(objects.cy[i].normal, pcy) - scalar_product_vecs(objects.cy[i].normal, objects.l[num_l].coord);
	t1 = t1 / t2;
	p = add_t_vecs(1, objects.l[num_l].coord, t1, add_t_vecs(1, pcy, -1, objects.l[num_l].coord));
	if (lenght_vecs(add_t_vecs(1, p, -1, h)) <= objects.cy[i].diam / 2)
		if (lenght_vecs(add_t_vecs(1, p, -1, objects.l[num_l].coord)) <= lenght_vecs(add_t_vecs(1, pcy, -1, objects.l[num_l].coord)))
		return (1);
	return (0);
}

int		shadow_cyhead1(t_objscene objects, int i, t_vector pcy, int num_l)
{
	t_vector p, h;
	float t1, t2;

	//h = add_t_vecs(1, objects.cy[i].coord, - objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(objects.cy[i].normal, objects.cy[i].normal)), objects.cy[i].normal);
	h = add_t_vecs(1, objects.cy[i].coord, objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(objects.cy[i].normal, objects.cy[i].normal)), objects.cy[i].normal);

	t1 = scalar_product_vecs(objects.cy[i].normal, h) - scalar_product_vecs(objects.cy[i].normal, objects.l[num_l].coord);
	t2 = scalar_product_vecs(objects.cy[i].normal, pcy) - scalar_product_vecs(objects.cy[i].normal, objects.l[num_l].coord);
	t1 = t1 / t2;
	p = add_t_vecs(1, objects.l[num_l].coord, t1, add_t_vecs(1, pcy, -1, objects.l[num_l].coord));
	if (lenght_vecs(add_t_vecs(1, p, -1, h)) <= objects.cy[i].diam / 2)
		if (lenght_vecs(add_t_vecs(1, p, -1, objects.l[num_l].coord)) <= lenght_vecs(add_t_vecs(1, pcy, -1, objects.l[num_l].coord)))
		return (1);
	return (0);
}

float		check_shadow_cy(int num_l, int num_cy, t_objscene objects, t_vector pt)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;
	t_vector p;

	i = 0;
	while (objects.cy[i].is)
	{
		if (i != num_cy)
		{
			//gen->scene.coord_v->pt, gen->scene.coord_0->objects.l[num_l].coord
			p = vec_product_vecs(add_t_vecs(1, pt, -1, objects.l[num_l].coord), objects.cy[i].normal);
			k[0] = fabs(scalar_product_vecs(add_t_vecs(1, objects.cy[i].coord, -1, objects.l[num_l].coord), p) / lenght_vecs(p));
			if (k[0] <= objects.cy[i].diam / 2)
			{
				p = add_t_vecs(1, pt, -1, objects.l[num_l].coord);
				k[0] = scalar_product_vecs(vec_product_vecs(p, objects.cy[i].normal), vec_product_vecs(p, objects.cy[i].normal)); //(Vn,Vn)
				k[1] = 2 * scalar_product_vecs(vec_product_vecs(p, objects.cy[i].normal), add_t_vecs(1, vec_product_vecs(objects.l[num_l].coord, objects.cy[i].normal), -1, vec_product_vecs(objects.cy[i].coord, objects.cy[i].normal))); // 2(Vn,On-Cn)
				k[2] = scalar_product_vecs(add_t_vecs(1, vec_product_vecs(objects.l[num_l].coord, objects.cy[i].normal), -1, vec_product_vecs(objects.cy[i].coord, objects.cy[i].normal)), add_t_vecs(1, vec_product_vecs(objects.l[num_l].coord, objects.cy[i].normal), -1, vec_product_vecs(objects.cy[i].coord, objects.cy[i].normal))) - scalar_product_vecs(objects.cy[i].normal, objects.cy[i].normal) * objects.cy[i].diam * objects.cy[i].diam / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					if ((t_n[0] > 0 && t_n[0] < 1) || (t_n[1] > 0 && t_n[1] < 1))
						return (0);
				}
				if (shadow_cyhead0(objects, i, pt, num_l) || shadow_cyhead1(objects, i, pt, num_l))
					return (0);
			}
		}
		i++;
	}
	return (1);
}
