#include "light_change.h"

float	light_change_sp(t_general gen, t_vector p, int i)
{
	t_vector lig;
	t_vector norm;
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objs.a.rat;
	num_l = 0;
	while (gen.objs.l[num_l].is)
	{
		norm = sum_vs(-1 / len_vec(sum_vs(1, p, -1, gen.objs.sp[i].cd)), p, 1 / len_vec(sum_vs( 1, p, -1, gen.objs.sp[i].cd)), gen.objs.sp[i].cd);
		lig = sum_vs( 1, p, -1, gen.objs.l[num_l].cd);
		if ((bright = dot_prv(norm, lig) / len_vec(lig)) < 0)
			bright = 0;

		res_br += gen.objs.l[num_l].br * bright * check_shadow(num_l, i, gen.objs, p);

		gen.objs.l[0].cl.x = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br
		: gen.objs.l[0].cl.x + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br;
		gen.objs.l[0].cl.y = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br
		: gen.objs.l[0].cl.y + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br;
		gen.objs.l[0].cl.z = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br
		: gen.objs.l[0].cl.z + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br;
		num_l++;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	gen.objs.sp[i].cl = sum_vs(res_br, sum_vs(0.4, gen.objs.sp[i].cl, 0.4, gen.objs.l[0].cl), 0.2 * res_br, gen.objs.a.cl);
	gen.objs.sp[i].cl.x = (gen.objs.sp[i].cl.x > 255) ? 255 : gen.objs.sp[i].cl.x;
	gen.objs.sp[i].cl.y = (gen.objs.sp[i].cl.y > 255) ? 255 : gen.objs.sp[i].cl.y;
	gen.objs.sp[i].cl.z = (gen.objs.sp[i].cl.z > 255) ? 255 : gen.objs.sp[i].cl.z;
	/*objects.sp[i].cl.x *= res_br;
	objects.sp[i].cl.y *= res_br;		//не цветное освещение
	objects.sp[i].cl.z *= res_br;*/
	return (ft_colorvec_unsint(1, gen.objs.sp[i].cl));
}

float	light_change_pl(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objs.a.rat;
	num_l = 0;
	while (gen.objs.l[num_l].is)
	{
		bright = 30 / len_vec(sum_vs(1, p, -1, gen.objs.l[num_l].cd));
		res_br += gen.objs.l[num_l].br * bright * (check_orient(gen.objs.pl[i].nm, gen.objs.l[num_l].cd, gen.scene.cdo, p) ? check_shadow(num_l, i + 100, gen.objs, p) : 0);

		gen.objs.l[0].cl.x = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br
		: gen.objs.l[0].cl.x + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br;
		gen.objs.l[0].cl.y = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br
		: gen.objs.l[0].cl.y + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br;
		gen.objs.l[0].cl.z = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br
		: gen.objs.l[0].cl.z + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objs.pl[i].cl = sum_vs(res_br, sum_vs(0.4, gen.objs.pl[i].cl, 0.4, gen.objs.l[0].cl), 0.2 * res_br, gen.objs.a.cl);
	gen.objs.pl[i].cl.x = (gen.objs.pl[i].cl.x > 255) ? 255 : gen.objs.pl[i].cl.x;
	gen.objs.pl[i].cl.y = (gen.objs.pl[i].cl.y > 255) ? 255 : gen.objs.pl[i].cl.y;
	gen.objs.pl[i].cl.z = (gen.objs.pl[i].cl.z > 255) ? 255 : gen.objs.pl[i].cl.z;

	return(ft_colorvec_unsint(1, gen.objs.pl[i].cl));
	(void) p;
	(void) i;
}

float	light_change_sq(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objs.a.rat;
	num_l = 0;
	while (gen.objs.l[num_l].is)
	{
		bright = 20 / len_vec(sum_vs(1, p, -1, gen.objs.l[num_l].cd));
		res_br += gen.objs.l[num_l].br * bright * (check_orient(gen.objs.sq[i].nm, gen.objs.l[num_l].cd, gen.scene.cdo, p) ? check_shadow(num_l, i + 200, gen.objs, p) : 0);

		gen.objs.l[0].cl.x = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br
		: gen.objs.l[0].cl.x + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br;
		gen.objs.l[0].cl.y = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br
		: gen.objs.l[0].cl.y + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br;
		gen.objs.l[0].cl.z = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br
		: gen.objs.l[0].cl.z + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objs.sq[i].cl = sum_vs(res_br, sum_vs(0.4, gen.objs.sq[i].cl, 0.4, gen.objs.l[0].cl), 0.2 * res_br, gen.objs.a.cl);
	gen.objs.sq[i].cl.x = (gen.objs.sq[i].cl.x > 255) ? 255 : gen.objs.sq[i].cl.x;
	gen.objs.sq[i].cl.y = (gen.objs.sq[i].cl.y > 255) ? 255 : gen.objs.sq[i].cl.y;
	gen.objs.sq[i].cl.z = (gen.objs.sq[i].cl.z > 255) ? 255 : gen.objs.sq[i].cl.z;

	return(ft_colorvec_unsint(1, gen.objs.sq[i].cl));
	(void) p;
	(void) i;
}

float	light_change_tr(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	int num_l;

	res_br = gen.objs.a.rat;
	num_l = 0;
	while (gen.objs.l[num_l].is)
	{
		bright = 20 / len_vec(sum_vs(1, p, -1, gen.objs.l[num_l].cd));
		res_br += gen.objs.l[num_l].br * bright * (check_orient(gen.objs.tr[i].nm, gen.objs.l[num_l].cd, gen.scene.cdo, p) ? check_shadow(num_l, i + 300, gen.objs, p) : 0);

		gen.objs.l[0].cl.x = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br
		: gen.objs.l[0].cl.x + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br;
		gen.objs.l[0].cl.y = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br
		: gen.objs.l[0].cl.y + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br;
		gen.objs.l[0].cl.z = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br
		: gen.objs.l[0].cl.z + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br;
		num_l++;
	}

	if (res_br > 1)
		res_br = 1;

	gen.objs.tr[i].cl = sum_vs(res_br, sum_vs(0.4, gen.objs.tr[i].cl, 0.4, gen.objs.l[0].cl), 0.2 * res_br, gen.objs.a.cl);
	gen.objs.tr[i].cl.x = (gen.objs.tr[i].cl.x > 255) ? 255 : gen.objs.tr[i].cl.x;
	gen.objs.tr[i].cl.y = (gen.objs.tr[i].cl.y > 255) ? 255 : gen.objs.tr[i].cl.y;
	gen.objs.tr[i].cl.z = (gen.objs.tr[i].cl.z > 255) ? 255 : gen.objs.tr[i].cl.z;

	return(ft_colorvec_unsint(1, gen.objs.tr[i].cl));
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

	res_br = gen.objs.a.rat;
	num_l = 0;
	while (gen.objs.l[num_l].is)
	{
		if (fl != 4)
		{
			bright = -dot_prv(gen.objs.cy[i].nm, sum_vs(1, gen.objs.cy[i].cd, -1, p)) / dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm);
			norm = sum_vs(-1, p, 1, sum_vs(1, gen.objs.cy[i].cd, bright, gen.objs.cy[i].nm));
			norm = sum_vs(1 / len_vec(norm), norm, 0, norm);
			lig = sum_vs( 1, p, -1, gen.objs.l[num_l].cd);
			if ((bright = dot_prv(norm, lig) / len_vec(lig)) < 0)
				bright = 0;
		}
		else
			bright = 20 / len_vec(sum_vs(1, p, -1, gen.objs.l[num_l].cd));

		res_br += gen.objs.l[num_l].br * bright * check_shadow(num_l, i + 400, gen.objs, p);

		gen.objs.l[0].cl.x = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br
		: gen.objs.l[0].cl.x + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.x * res_br;
		gen.objs.l[0].cl.y = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br
		: gen.objs.l[0].cl.y + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.y * res_br;
		gen.objs.l[0].cl.z = (num_l == 0) ? gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br
		: gen.objs.l[0].cl.z + gen.objs.l[num_l].br * gen.objs.l[num_l].cl.z * res_br;
		num_l++;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	gen.objs.cy[i].cl = sum_vs(res_br, sum_vs(0.4, gen.objs.cy[i].cl, 0.4, gen.objs.l[0].cl), 0.2 * res_br, gen.objs.a.cl);
	gen.objs.cy[i].cl.x = (gen.objs.cy[i].cl.x > 255) ? 255 : gen.objs.cy[i].cl.x;
	gen.objs.cy[i].cl.y = (gen.objs.cy[i].cl.y > 255) ? 255 : gen.objs.cy[i].cl.y;
	gen.objs.cy[i].cl.z = (gen.objs.cy[i].cl.z > 255) ? 255 : gen.objs.cy[i].cl.z;
	return(ft_colorvec_unsint(1, gen.objs.cy[i].cl));
	(void) p;
	(void) i;
}
