#include "light_change.h"

float	light_change_sp(t_general gen, t_vector p, int i)
{
	t_vector lig;
	t_vector norm;
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objects.a.rat_amlig;
	num_l = 0;
	while (gen.objects.l[num_l].is)
	{
		norm = add_t_vecs(-1 / lenght_vecs(add_t_vecs(1, p, -1, gen.objects.sp[i].coord)), p, 1 / lenght_vecs(add_t_vecs( 1, p, -1, gen.objects.sp[i].coord)), gen.objects.sp[i].coord);
		lig = add_t_vecs( 1, p, -1, gen.objects.l[num_l].coord);
		if ((bright = scalar_product_vecs(norm, lig) / lenght_vecs(lig)) < 0)
			bright = 0;

		res_br += gen.objects.l[num_l].brirat * bright * check_shadow(num_l, i, gen.objects, p);

		gen.objects.l[0].color.x = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br
		: gen.objects.l[0].color.x + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br;
		gen.objects.l[0].color.y = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br
		: gen.objects.l[0].color.y + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br;
		gen.objects.l[0].color.z = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br
		: gen.objects.l[0].color.z + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br;
		num_l++;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	gen.objects.sp[i].color = add_t_vecs(res_br, add_t_vecs(0.4, gen.objects.sp[i].color, 0.4, gen.objects.l[0].color), 0.2 * res_br, gen.objects.a.color);
	gen.objects.sp[i].color.x = (gen.objects.sp[i].color.x > 255) ? 255 : gen.objects.sp[i].color.x;
	gen.objects.sp[i].color.y = (gen.objects.sp[i].color.y > 255) ? 255 : gen.objects.sp[i].color.y;
	gen.objects.sp[i].color.z = (gen.objects.sp[i].color.z > 255) ? 255 : gen.objects.sp[i].color.z;
	/*objects.sp[i].color.x *= res_br;
	objects.sp[i].color.y *= res_br;		//не цветное освещение
	objects.sp[i].color.z *= res_br;*/
	return (ft_colorvec_unsint(1, gen.objects.sp[i].color));
}

float	light_change_pl(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objects.a.rat_amlig;
	num_l = 0;
	while (gen.objects.l[num_l].is)
	{
		bright = 30 / lenght_vecs(add_t_vecs(1, p, -1, gen.objects.l[num_l].coord));
		res_br += gen.objects.l[num_l].brirat * bright * (check_orient(num_l, i, gen, p) ? check_shadow(num_l, i + 100, gen.objects, p) : 0);

		gen.objects.l[0].color.x = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br
		: gen.objects.l[0].color.x + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br;
		gen.objects.l[0].color.y = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br
		: gen.objects.l[0].color.y + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br;
		gen.objects.l[0].color.z = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br
		: gen.objects.l[0].color.z + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objects.pl[i].color = add_t_vecs(res_br, add_t_vecs(0.4, gen.objects.pl[i].color, 0.4, gen.objects.l[0].color), 0.2 * res_br, gen.objects.a.color);
	gen.objects.pl[i].color.x = (gen.objects.pl[i].color.x > 255) ? 255 : gen.objects.pl[i].color.x;
	gen.objects.pl[i].color.y = (gen.objects.pl[i].color.y > 255) ? 255 : gen.objects.pl[i].color.y;
	gen.objects.pl[i].color.z = (gen.objects.pl[i].color.z > 255) ? 255 : gen.objects.pl[i].color.z;

	return(ft_colorvec_unsint(1, gen.objects.pl[i].color));
	(void) p;
	(void) i;
}

float	light_change_sq(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objects.a.rat_amlig;
	num_l = 0;
	while (gen.objects.l[num_l].is)
	{
		bright = 20 / lenght_vecs(add_t_vecs(1, p, -1, gen.objects.l[num_l].coord));
		res_br += gen.objects.l[num_l].brirat * bright * (check_orient(num_l, i, gen, p) ? check_shadow(num_l, i + 200, gen.objects, p) : 0);

		gen.objects.l[0].color.x = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br
		: gen.objects.l[0].color.x + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br;
		gen.objects.l[0].color.y = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br
		: gen.objects.l[0].color.y + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br;
		gen.objects.l[0].color.z = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br
		: gen.objects.l[0].color.z + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objects.sq[i].color = add_t_vecs(res_br, add_t_vecs(0.4, gen.objects.sq[i].color, 0.4, gen.objects.l[0].color), 0.2 * res_br, gen.objects.a.color);
	gen.objects.sq[i].color.x = (gen.objects.sq[i].color.x > 255) ? 255 : gen.objects.sq[i].color.x;
	gen.objects.sq[i].color.y = (gen.objects.sq[i].color.y > 255) ? 255 : gen.objects.sq[i].color.y;
	gen.objects.sq[i].color.z = (gen.objects.sq[i].color.z > 255) ? 255 : gen.objects.sq[i].color.z;

	return(ft_colorvec_unsint(1, gen.objects.sq[i].color));
	(void) p;
	(void) i;
}

float	light_change_tr(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objects.a.rat_amlig;
	num_l = 0;
	while (gen.objects.l[num_l].is)
	{
		bright = 20 / lenght_vecs(add_t_vecs(1, p, -1, gen.objects.l[num_l].coord));
		res_br += gen.objects.l[num_l].brirat * bright * (check_orient(num_l, i, gen, p) ? check_shadow(num_l, i + 300, gen.objects, p) : 0);

		gen.objects.l[0].color.x = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br
		: gen.objects.l[0].color.x + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br;
		gen.objects.l[0].color.y = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br
		: gen.objects.l[0].color.y + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br;
		gen.objects.l[0].color.z = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br
		: gen.objects.l[0].color.z + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objects.tr[i].color = add_t_vecs(res_br, add_t_vecs(0.4, gen.objects.tr[i].color, 0.4, gen.objects.l[0].color), 0.2 * res_br, gen.objects.a.color);
	gen.objects.tr[i].color.x = (gen.objects.tr[i].color.x > 255) ? 255 : gen.objects.tr[i].color.x;
	gen.objects.tr[i].color.y = (gen.objects.tr[i].color.y > 255) ? 255 : gen.objects.tr[i].color.y;
	gen.objects.tr[i].color.z = (gen.objects.tr[i].color.z > 255) ? 255 : gen.objects.tr[i].color.z;

	return(ft_colorvec_unsint(1, gen.objects.tr[i].color));
	(void) p;
	(void) i;
}

float	light_change_cy(t_general gen, t_vector p, int i, int fl)
{
	t_vector lig;
	t_vector norm;
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objects.a.rat_amlig;
	num_l = 0;
	while (gen.objects.l[num_l].is)
	{
		if (fl != 4)
		{
			bright = -scalar_product_vecs(gen.objects.cy[i].normal, add_t_vecs(1, gen.objects.cy[i].coord, -1, p)) / scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal);
			norm = add_t_vecs(-1, p, 1, add_t_vecs(1, gen.objects.cy[i].coord, bright, gen.objects.cy[i].normal));
			norm = add_t_vecs(1 / lenght_vecs(norm), norm, 0, norm);
			lig = add_t_vecs( 1, p, -1, gen.objects.l[num_l].coord);
			if ((bright = scalar_product_vecs(norm, lig) / lenght_vecs(lig)) < 0)
				bright = 0;
		}
		else
			bright = 20 / lenght_vecs(add_t_vecs(1, p, -1, gen.objects.l[num_l].coord));

		res_br += gen.objects.l[num_l].brirat * bright * check_shadow(num_l, i + 400, gen.objects, p);

		gen.objects.l[0].color.x = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br
		: gen.objects.l[0].color.x + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.x * res_br;
		gen.objects.l[0].color.y = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br
		: gen.objects.l[0].color.y + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.y * res_br;
		gen.objects.l[0].color.z = (num_l == 0) ? gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br
		: gen.objects.l[0].color.z + gen.objects.l[num_l].brirat * gen.objects.l[num_l].color.z * res_br;
		num_l++;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	gen.objects.cy[i].color = add_t_vecs(res_br, add_t_vecs(0.4, gen.objects.cy[i].color, 0.4, gen.objects.l[0].color), 0.2 * res_br, gen.objects.a.color);
	gen.objects.cy[i].color.x = (gen.objects.cy[i].color.x > 255) ? 255 : gen.objects.cy[i].color.x;
	gen.objects.cy[i].color.y = (gen.objects.cy[i].color.y > 255) ? 255 : gen.objects.cy[i].color.y;
	gen.objects.cy[i].color.z = (gen.objects.cy[i].color.z > 255) ? 255 : gen.objects.cy[i].color.z;
	return(ft_colorvec_unsint(1, gen.objects.cy[i].color));
	(void) p;
	(void) i;
}
