#include "belong_to_obj.h"

int	belong_to_sphere(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	fl = 1;
	/*if (gen->pix.x == 0 && gen->pix.y == 0)
		printf(" 0   0  %f, %f, %f\n", gen->scene.cdv.x, gen->scene.cdv.y, gen->scene.cdv.z);
	if (gen->pix.x == 0 && gen->pix.y == 512)
		printf(" 0  512 %f, %f, %f\n", gen->scene.cdv.x, gen->scene.cdv.y, gen->scene.cdv.z);
	if (gen->pix.x == 512 && gen->pix.y == 0)
		printf("512  0  %f, %f, %f\n", gen->scene.cdv.x, gen->scene.cdv.y, gen->scene.cdv.z);
	if (gen->pix.x == 512 && gen->pix.y == 512)
		printf("512 512 %f, %f, %f\n", gen->scene.cdv.x, gen->scene.cdv.y, gen->scene.cdv.z);*/
	//1 842 183 // без проверки (первый if)
	//1 483 772 // C-O
	p = sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo);
	k[0] = len_vec(cross_prv(sum_vs(1, gen->objs.sp[(int)gen->pix.z].cd, -1, gen->scene.cdo), p)) / len_vec(p);
	if (k[0] <= gen->objs.sp[(int)gen->pix.z].d * 2)
	{
		(*i)++;
		k[0] = dot_prv(p, p);
		k[1] = 2 * dot_prv(sum_vs( 1, gen->scene.cdo, -1, gen->objs.sp[(int)gen->pix.z].cd), p);
		k[2] = dot_prv(sum_vs( 1, gen->scene.cdo, -1, gen->objs.sp[(int)gen->pix.z].cd), sum_vs( 1, gen->scene.cdo, -1, gen->objs.sp[(int)gen->pix.z].cd)) - gen->objs.sp[(int)gen->pix.z].d * gen->objs.sp[(int)gen->pix.z].d / 4;
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
			fl = 0;
		t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
		t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
		if ((t[0] < 0 || t[1] <= t[0]))
			p = sum_vs(1, gen->scene.cdo, t[1], p);
		else //if ((t[1] < 1 || t[0] < t[1]))
			p = sum_vs(1, gen->scene.cdo, t[0], p);

		if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
			fl = 0;

		/*(fl == 1 && z == 0) fun;
		(fl == 1 && z != 0) fun;
		(fl == 0 && z == 0) -5;
		(fl == 0 && z != 0) color;*/
		gen->cl = (fl == 1) ? light_change_sp(*gen, p, (int)gen->pix.z) : gen->cl;
	}
	gen->pix.z += 1;
	if (gen->objs.sp[(int)gen->pix.z].is == 1)
		gen->cl = belong_to_sphere(gen, i);
	return (gen->cl);
	(void)i;
}

int		belong_to_plane(t_general *gen, int *i)
{
	t_vector p;
	float t, t1, t2;

	(*i)++;

	t1 = dot_prv(gen->objs.pl[(int)gen->pix.z].nm, gen->objs.pl[(int)gen->pix.z].cd) - dot_prv(gen->objs.pl[(int)gen->pix.z].nm, gen->scene.cdo);
	t2 = dot_prv(gen->objs.pl[(int)gen->pix.z].nm, gen->scene.cdv) - dot_prv(gen->objs.pl[(int)gen->pix.z].nm, gen->scene.cdo);
	t = t1 / t2;
	ft_write_xyz(&p, 0, 0, 0);
	p = sum_vs(1, gen->scene.cdo, t, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

	if (!check_see_objs(*gen, p, 100 + (int)gen->pix.z) && (t > 1 && t < 200))
		gen->cl = light_change_pl(*gen, p, (int)gen->pix.z);

	gen->pix.z += 1;
	if (gen->objs.pl[(int)gen->pix.z].is == 1)
		gen->cl = belong_to_plane(gen, i);
	return (gen->cl);
}

int		belong_to_square(t_general *gen, int *i)
{
	t_vector p;
	float t1, t2;

	(*i)++;

	t1 = dot_prv(gen->objs.sq[(int)gen->pix.z].nm, gen->objs.sq[(int)gen->pix.z].cd) - dot_prv(gen->objs.sq[(int)gen->pix.z].nm, gen->scene.cdo);
	t2 = dot_prv(gen->objs.sq[(int)gen->pix.z].nm, gen->scene.cdv) - dot_prv(gen->objs.sq[(int)gen->pix.z].nm, gen->scene.cdo);
	t1 = t1 / t2;
	p = sum_vs(1, gen->scene.cdo, t1, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

	if (point_in_square(gen->objs.sq[(int)gen->pix.z], p))
		if (!check_see_objs(*gen, p, 200 + (int)gen->pix.z))
			gen->cl = light_change_sq(*gen, p, (int)gen->pix.z);
	gen->pix.z += 1;
	if (gen->objs.sq[(int)gen->pix.z].is == 1)
		gen->cl = belong_to_square(gen, i);
	return (gen->cl);
}

int		belong_to_triangle(t_general *gen, int *i)
{
	t_vector p;
	float t1, t2;

	(*i)++;

	t1 = dot_prv(gen->objs.tr[(int)gen->pix.z].nm, gen->objs.tr[(int)gen->pix.z].cd1) - dot_prv(gen->objs.tr[(int)gen->pix.z].nm, gen->scene.cdo);
	t2 = dot_prv(gen->objs.tr[(int)gen->pix.z].nm, gen->scene.cdv) - dot_prv(gen->objs.tr[(int)gen->pix.z].nm, gen->scene.cdo);
	t1 = t1 / t2;
	p = sum_vs(1, gen->scene.cdo, t1, sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));

	if (point_in_triangle(gen->objs.tr[(int)gen->pix.z], p))
		if (!check_see_objs(*gen, p, 300 + (int)gen->pix.z))
			gen->cl = light_change_tr(*gen, p, (int)gen->pix.z);
	gen->pix.z += 1;
	if (gen->objs.tr[(int)gen->pix.z].is == 1)
		gen->cl = belong_to_triangle(gen, i);
	return (gen->cl);
}

int		belong_to_cylinder(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	fl = 1;
	p = cross_prv(sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo), gen->objs.cy[(int)gen->pix.z].nm);
	k[0] = fabs(dot_prv(sum_vs(1, gen->objs.cy[(int)gen->pix.z].cd, -1, gen->scene.cdo), p) / len_vec(p));
	if (k[0] <= gen->objs.cy[(int)gen->pix.z].d / 2)
	{
		(*i)++;
		p = sum_vs(1, gen->scene.cdv, -1, gen->scene.cdo);
		k[0] = dot_prv(cross_prv(p, gen->objs.cy[(int)gen->pix.z].nm), cross_prv(p, gen->objs.cy[(int)gen->pix.z].nm)); //(Vn,Vn)
		k[1] = 2 * dot_prv(cross_prv(p, gen->objs.cy[(int)gen->pix.z].nm), sum_vs(1, cross_prv(gen->scene.cdo, gen->objs.cy[(int)gen->pix.z].nm), -1, cross_prv(gen->objs.cy[(int)gen->pix.z].cd, gen->objs.cy[(int)gen->pix.z].nm))); // 2(Vn,On-Cn)
		k[2] = dot_prv(sum_vs(1, cross_prv(gen->scene.cdo, gen->objs.cy[(int)gen->pix.z].nm), -1, cross_prv(gen->objs.cy[(int)gen->pix.z].cd, gen->objs.cy[(int)gen->pix.z].nm)), sum_vs(1, cross_prv(gen->scene.cdo, gen->objs.cy[(int)gen->pix.z].nm), -1, cross_prv(gen->objs.cy[(int)gen->pix.z].cd, gen->objs.cy[(int)gen->pix.z].nm))) - dot_prv(gen->objs.cy[(int)gen->pix.z].nm, gen->objs.cy[(int)gen->pix.z].nm) * gen->objs.cy[(int)gen->pix.z].d * gen->objs.cy[(int)gen->pix.z].d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		if (t[1] < 0 || k[0] == 0)
			fl = 0;
		t[0] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
		t[1] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
		/*if (t[0] > t[1]) //проверка что t[0] точно меньше t[1]
		{	k[2] = t[0];	t[0] = t[1];	t[1] = k[2];	}*/
		if (t[0] > 1 && fl > 0)
		{
			p = sum_vs(1, gen->scene.cdo, t[0], sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));
			if (len_vec(sum_vs(1, p, -1, gen->objs.cy[(int)gen->pix.z].cd)) <= sqrt(gen->objs.cy[(int)gen->pix.z].h * gen->objs.cy[(int)gen->pix.z].h / 4 + gen->objs.cy[(int)gen->pix.z].d * gen->objs.cy[(int)gen->pix.z].d / 4))
				fl = 2;
		}
		if (t[1] > 1 && fl > 0 && fl != 2)
		{
			p = sum_vs(1, gen->scene.cdo, t[1], sum_vs( 1, gen->scene.cdv, -1, gen->scene.cdo));
			if (len_vec(sum_vs(1, p, -1, gen->objs.cy[(int)gen->pix.z].cd)) <= sqrt(gen->objs.cy[(int)gen->pix.z].h * gen->objs.cy[(int)gen->pix.z].h / 4 + gen->objs.cy[(int)gen->pix.z].d * gen->objs.cy[(int)gen->pix.z].d / 4))
				fl = 3;
		}

		fl = belong_to_cyhead0(*gen, (int)gen->pix.z, &p, fl);
		fl = belong_to_cyhead1(*gen, (int)gen->pix.z, &p, fl);
		if (check_see_objs(*gen, p, 400 + (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
			fl = 0;

		gen->cl = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z, fl) : gen->cl;
	}
	//gen->pix.z += 1;
	//if (gen->objs.tr[(int)gen->pix.z].is == 1)
		//gen->cl = belong_to_cylinder(gen, i);
	return (gen->cl);
	(void)k;
	(void)t;
	(void)p;
}

int		belong_to_cyhead0(t_general gen, int i, t_vector *pcy, int fl)
{
	t_vector p, h;
	float t1, t2;

	h = sum_vs(1, gen.objs.cy[i].cd, - gen.objs.cy[i].h / 2 / sqrt(dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm)), gen.objs.cy[i].nm);
	//h = sum_vs(1, gen.objs.cy[i].cd, gen.objs.cy[i].h / 2 / sqrt(dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm)), gen.objs.cy[i].nm);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t1 = dot_prv(gen.objs.cy[i].nm, h) - dot_prv(gen.objs.cy[i].nm, gen.scene.cdo);
	t2 = dot_prv(gen.objs.cy[i].nm, gen.scene.cdv) - dot_prv(gen.objs.cy[i].nm, gen.scene.cdo);
	t1 = t1 / t2;
	p = sum_vs(1, gen.scene.cdo, t1, sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (len_vec(sum_vs(1, p, -1, h)) <= gen.objs.cy[i].d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
}

int		belong_to_cyhead1(t_general gen, int i, t_vector *pcy, int fl)
{
	t_vector p, h;
	float t1, t2;

	//h = sum_vs(1, gen.objs.cy[i].cd, - gen.objs.cy[i].h / 2 / sqrt(dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm)), gen.objs.cy[i].nm);
	h = sum_vs(1, gen.objs.cy[i].cd, gen.objs.cy[i].h / 2 / sqrt(dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm)), gen.objs.cy[i].nm);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t1 = dot_prv(gen.objs.cy[i].nm, h) - dot_prv(gen.objs.cy[i].nm, gen.scene.cdo);
	t2 = dot_prv(gen.objs.cy[i].nm, gen.scene.cdv) - dot_prv(gen.objs.cy[i].nm, gen.scene.cdo);
	t1 = t1 / t2;
	p = sum_vs(1, gen.scene.cdo, t1, sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo));
	if (len_vec(sum_vs(1, p, -1, h)) <= gen.objs.cy[i].d / 2)
		if ((fl > 1 && len_vec(sum_vs(1, p, -1, gen.scene.cdo)) <= len_vec(sum_vs(1, *pcy, -1, gen.scene.cdo))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
	//return (gen->cl);
}
