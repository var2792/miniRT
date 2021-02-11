#include "check_shadows.h"

float		check_shadow(int num_l, int num_ob, t_scobjs objects, t_vector p)
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

float		check_shadow_sp(int num_l, int num_sp, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;

	i = 0;
	while (objects.sp[i].is)
	{
		if (i != num_sp)
		{
			k[0] = len_vec(cross_prv(sum_vs(1, objects.sp[i].cd, -1, objects.l[num_l].cd), sum_vs(1, p, -1, objects.l[num_l].cd))) / len_vec(sum_vs(1, p, -1, objects.l[num_l].cd));
			if (k[0] <= objects.sp[i].d * 2)
			{
				k[0] = dot_prv(sum_vs(1, p, -1, objects.l[num_l].cd), sum_vs( 1, p, -1, objects.l[num_l].cd));
				k[1] = 2 * dot_prv(sum_vs(1, objects.l[num_l].cd, -1, objects.sp[i].cd), sum_vs( 1, p, -1, objects.l[num_l].cd));
				k[2] = dot_prv(sum_vs(1, objects.l[num_l].cd, -1, objects.sp[i].cd), sum_vs(1, objects.l[num_l].cd, -1, objects.sp[i].cd)) - objects.sp[i].d * objects.sp[i].d / 4;
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

float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p)
{
	float alfa;
	t_vector t;

	t = sum_vs(1, p, -1, cor_0);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		normal = sum_vs(0, t, -1, normal);
	t = sum_vs(1, p, -1, l);
	alfa = dot_prv(t, normal) / len_vec(t) / len_vec(normal);
	if (alfa < 0)
		return (0);
	return (1);
}

float		check_shadow_pl(int num_l, int num_pl, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2, t;
	int i;

	i = 0;
	while (objects.pl[i].is)
	{
		if (i != num_pl)
		{
			t1 = dot_prv(objects.pl[i].nm, objects.pl[i].cd) - dot_prv(objects.pl[i].nm, objects.l[num_l].cd);
			t2 = dot_prv(objects.pl[i].nm, p) - dot_prv(objects.pl[i].nm, objects.l[num_l].cd);
			t = t1 / t2;
			if (t >= 0 && t <= 1)
				return (0);
		}
		i++;
	}
	return (1);
}

float		check_shadow_sq(int num_l, int num_sq, t_scobjs objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float t1, t2;
	int i;
	t_vector t;

	i = 0;
	while (objects.sq[i].is)
	{
		if (i != num_sq)
		{
			t1 = dot_prv(objects.sq[i].nm, objects.sq[i].cd) - dot_prv(objects.sq[i].nm, objects.l[num_l].cd);
			t2 = dot_prv(objects.sq[i].nm, p) - dot_prv(objects.sq[i].nm, objects.l[num_l].cd);
			t1 = t1 / t2;
			t = sum_vs(1, objects.l[num_l].cd, t1, sum_vs( 1, p, -1, objects.l[num_l].cd));

			if (point_in_square(objects.sq[i], t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		i++;
	}
	return (1);
}

float		check_shadow_tr(int num_l, int num_tr, t_scobjs objects, t_vector p)
{
	float t1, t2;
	int i;
	t_vector t;

	i = 0;
	while (objects.tr[i].is)
	{
		if (i != num_tr)
		{
			t1 = dot_prv(objects.tr[i].nm, objects.tr[i].cd1) - dot_prv(objects.tr[i].nm, objects.l[num_l].cd);
			t2 = dot_prv(objects.tr[i].nm, p) - dot_prv(objects.tr[i].nm, objects.l[num_l].cd);
			t1 = t1 / t2;
			t = sum_vs(1, objects.l[num_l].cd, t1, sum_vs( 1, p, -1, objects.l[num_l].cd));
			if (point_in_triangle(objects.tr[i], t))
				if (t1 >= 0 && t1 <= 1)
					return (0);
		}
		i++;
	}
	return (1);
}

int		shadow_cyhead0(t_scobjs objects, int i, t_vector pcy, int num_l)
{
	t_vector p, h;
	float t1, t2;

	h = sum_vs(1, objects.cy[i].cd, - objects.cy[i].h / 2 / sqrt(dot_prv(objects.cy[i].nm, objects.cy[i].nm)), objects.cy[i].nm);
	//h = sum_vs(1, objects.cy[i].cd, objects.cy[i].h / 2 / sqrt(dot_prv(objects.cy[i].nm, objects.cy[i].nm)), objects.cy[i].nm);

	t1 = dot_prv(objects.cy[i].nm, h) - dot_prv(objects.cy[i].nm, objects.l[num_l].cd);
	t2 = dot_prv(objects.cy[i].nm, pcy) - dot_prv(objects.cy[i].nm, objects.l[num_l].cd);
	t1 = t1 / t2;
	p = sum_vs(1, objects.l[num_l].cd, t1, sum_vs(1, pcy, -1, objects.l[num_l].cd));
	if (len_vec(sum_vs(1, p, -1, h)) <= objects.cy[i].d / 2)
		if (len_vec(sum_vs(1, p, -1, objects.l[num_l].cd)) <= len_vec(sum_vs(1, pcy, -1, objects.l[num_l].cd)))
		return (1);
	return (0);
}

int		shadow_cyhead1(t_scobjs objects, int i, t_vector pcy, int num_l)
{
	t_vector p, h;
	float t1, t2;

	//h = sum_vs(1, objects.cy[i].cd, - objects.cy[i].h / 2 / sqrt(dot_prv(objects.cy[i].nm, objects.cy[i].nm)), objects.cy[i].nm);
	h = sum_vs(1, objects.cy[i].cd, objects.cy[i].h / 2 / sqrt(dot_prv(objects.cy[i].nm, objects.cy[i].nm)), objects.cy[i].nm);

	t1 = dot_prv(objects.cy[i].nm, h) - dot_prv(objects.cy[i].nm, objects.l[num_l].cd);
	t2 = dot_prv(objects.cy[i].nm, pcy) - dot_prv(objects.cy[i].nm, objects.l[num_l].cd);
	t1 = t1 / t2;
	p = sum_vs(1, objects.l[num_l].cd, t1, sum_vs(1, pcy, -1, objects.l[num_l].cd));
	if (len_vec(sum_vs(1, p, -1, h)) <= objects.cy[i].d / 2)
		if (len_vec(sum_vs(1, p, -1, objects.l[num_l].cd)) <= len_vec(sum_vs(1, pcy, -1, objects.l[num_l].cd)))
		return (1);
	return (0);
}

float		check_shadow_cy(int num_l, int num_cy, t_scobjs objects, t_vector pt)
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
			//gen->scene.cdv->pt, gen->scene.cdo->objs.l[num_l].cd
			p = cross_prv(sum_vs(1, pt, -1, objects.l[num_l].cd), objects.cy[i].nm);
			k[0] = fabs(dot_prv(sum_vs(1, objects.cy[i].cd, -1, objects.l[num_l].cd), p) / len_vec(p));
			if (k[0] <= objects.cy[i].d / 2)
			{
				p = sum_vs(1, pt, -1, objects.l[num_l].cd);
				k[0] = dot_prv(cross_prv(p, objects.cy[i].nm), cross_prv(p, objects.cy[i].nm)); //(Vn,Vn)
				k[1] = 2 * dot_prv(cross_prv(p, objects.cy[i].nm), sum_vs(1, cross_prv(objects.l[num_l].cd, objects.cy[i].nm), -1, cross_prv(objects.cy[i].cd, objects.cy[i].nm))); // 2(Vn,On-Cn)
				k[2] = dot_prv(sum_vs(1, cross_prv(objects.l[num_l].cd, objects.cy[i].nm), -1, cross_prv(objects.cy[i].cd, objects.cy[i].nm)), sum_vs(1, cross_prv(objects.l[num_l].cd, objects.cy[i].nm), -1, cross_prv(objects.cy[i].cd, objects.cy[i].nm))) - dot_prv(objects.cy[i].nm, objects.cy[i].nm) * objects.cy[i].d * objects.cy[i].d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
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
