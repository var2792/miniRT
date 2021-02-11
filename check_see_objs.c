# include "check_see_objs.h"

int		check_see_objs(t_general gen, t_vector ptr, int num_ob)
{
	int res;

	res = 0;
	if (num_ob > -1 && num_ob < 100) //sphere
		res = check_see_sp(gen, ptr, num_ob);
	else
		res = check_see_sp(gen, ptr, -1);

	if (num_ob > 99 && num_ob < 200) //plane
		res = (res == 0) ? check_see_pl(gen, ptr, num_ob - 100) : res;
	else
		res = (res == 0) ? check_see_pl(gen, ptr, -1) : res;

	if (num_ob > 199 && num_ob < 300) //square
		res = (res == 0) ? check_see_sq(gen, ptr, num_ob - 200) : res;
	else
		res = (res == 0) ? check_see_sq(gen, ptr, -1) : res;

	if (num_ob > 299 && num_ob < 400) //triangle
		res = (res == 0) ? check_see_tr(gen, ptr, num_ob - 300) : res;
	else
		res = (res == 0) ? check_see_tr(gen, ptr, -1) : res;

	if (num_ob > 399 && num_ob < 500) //cylinder
		res = (res == 0) ? check_see_cy(gen, ptr, num_ob - 400) : res;
	else
		res = (res == 0) ? check_see_cy(gen, ptr, -1) : res;

	return (res);
}

int		check_see_sp(t_general gen, t_vector ptr, int num_sp)
{
	float k[3];
	float t_n[2];
	int i;
	t_vector p;

	i = 0;
	while (gen.objs.sp[i].is)
	{
		if (i != num_sp)
		{
			p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
			k[0] = len_vec(cross_prv(sum_vs(1, gen.objs.sp[i].cd, -1, gen.scene.cdo), p)) / len_vec(p);
			if (k[0] <= gen.objs.sp[i].d * 2)
			{
				k[0] = dot_prv(p, p);
				k[1] = 2 * dot_prv(sum_vs( 1, gen.scene.cdo, -1, gen.objs.sp[i].cd), p);
				k[2] = dot_prv(sum_vs( 1, gen.scene.cdo, -1, gen.objs.sp[i].cd), sum_vs( 1, gen.scene.cdo, -1, gen.objs.sp[i].cd)) - gen.objs.sp[i].d * gen.objs.sp[i].d / 4;
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (t_n[0] < 1 && t_n[1] < 0.01 && t_n[1] > -0.01) ? -5 : (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					if ((t_n[0] < 0 || t_n[1] <= t_n[0]))
						p = sum_vs(1, gen.scene.cdo, t_n[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
					else
						p = sum_vs(1, gen.scene.cdo, t_n[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));

					if (len_vec(sum_vs(1, p, -1, gen.objs.c[gen.num_cam].cd)) <= len_vec(sum_vs(1, ptr, -1, gen.objs.c[gen.num_cam].cd)))
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}


int		check_see_pl(t_general gen, t_vector ptr, int num_pl)
{
	int i;
	float t, t1, t2;
	t_vector p;

	i = 0;
	while (gen.objs.pl[i].is)
	{
		if (i != num_pl)
		{
			t1 = dot_prv(gen.objs.pl[i].nm, gen.objs.pl[i].cd) - dot_prv(gen.objs.pl[i].nm, gen.objs.c[gen.num_cam].cd);
			t2 = dot_prv(gen.objs.pl[i].nm, gen.scene.cdv) - dot_prv(gen.objs.pl[i].nm, gen.objs.c[gen.num_cam].cd);
			t = t1 / t2;
			//printf("PL %f\n", t);
			p = sum_vs(1, gen.scene.cdo, t, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if ((t >= 1 && t < 200) && len_vec(sum_vs(1, p, -1, gen.objs.c[gen.num_cam].cd)) <= len_vec(sum_vs(1, ptr, -1, gen.objs.c[gen.num_cam].cd)))
					return (1);
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_sq(t_general gen, t_vector ptr, int num_sq)
{
	int i;
	float t1, t2;
	t_vector p;

	i = 0;
	while (gen.objs.sq[i].is)
	{
		if (i != num_sq)
		{
			t1 = dot_prv(gen.objs.sq[i].nm, gen.objs.sq[i].cd) - dot_prv(gen.objs.sq[i].nm, gen.objs.c[gen.num_cam].cd);
			t2 = dot_prv(gen.objs.sq[i].nm, gen.scene.cdv) - dot_prv(gen.objs.sq[i].nm, gen.objs.c[gen.num_cam].cd);
			t1 = t1 / t2;
	//printf("PL %f\n", t);
			p = sum_vs(1, gen.scene.cdo, t1, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if (point_in_square(gen.objs.sq[i], p))
				if (len_vec(sum_vs(1, p, -1, gen.objs.c[gen.num_cam].cd)) <= len_vec(sum_vs(1, ptr, -1, gen.objs.c[gen.num_cam].cd)))
					return (1);
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_tr(t_general gen, t_vector ptr, int num_tr)
{
	int i;
	float t1, t2;
	t_vector p;

	i = 0;
	while (gen.objs.tr[i].is)
	{
		if (i != num_tr)
		{
			t1 = dot_prv(gen.objs.tr[i].nm, gen.objs.tr[i].cd1) - dot_prv(gen.objs.tr[i].nm, gen.objs.c[gen.num_cam].cd);
			t2 = dot_prv(gen.objs.tr[i].nm, gen.scene.cdv) - dot_prv(gen.objs.tr[i].nm, gen.objs.c[gen.num_cam].cd);
			t1 = t1 / t2;
	//printf("PL %f\n", t);
			p = sum_vs(1, gen.scene.cdo, t1, sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
			if (point_in_triangle(gen.objs.tr[i], p))
				if (len_vec(sum_vs(1, p, -1, gen.objs.c[gen.num_cam].cd)) <= len_vec(sum_vs(1, ptr, -1, gen.objs.c[gen.num_cam].cd)))
					return (1);
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

int		check_see_cy(t_general gen, t_vector ptr, int num_cy)
{
	float k[3];
	float t_n[2];
	int i;
	int fl;
	t_vector p;

	i = 0;
	while (gen.objs.cy[i].is)
	{
		if (i != num_cy)
		{
			p = cross_prv(sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo), gen.objs.cy[i].nm);
			k[0] = fabs(dot_prv(sum_vs(1, gen.objs.cy[i].cd, -1, gen.scene.cdo), p) / len_vec(p));
			if (k[0] <= gen.objs.cy[i].d / 2)
			{
				fl = 1;
				p = sum_vs(1, gen.scene.cdv, -1, gen.scene.cdo);
				k[0] = dot_prv(cross_prv(p, gen.objs.cy[i].nm), cross_prv(p, gen.objs.cy[i].nm)); //(Vn,Vn)
				k[1] = 2 * dot_prv(cross_prv(p, gen.objs.cy[i].nm), sum_vs(1, cross_prv(gen.scene.cdo, gen.objs.cy[i].nm), -1, cross_prv(gen.objs.cy[i].cd, gen.objs.cy[i].nm))); // 2(Vn,On-Cn)
				k[2] = dot_prv(sum_vs(1, cross_prv(gen.scene.cdo, gen.objs.cy[i].nm), -1, cross_prv(gen.objs.cy[i].cd, gen.objs.cy[i].nm)), sum_vs(1, cross_prv(gen.scene.cdo, gen.objs.cy[i].nm), -1, cross_prv(gen.objs.cy[i].cd, gen.objs.cy[i].nm))) - dot_prv(gen.objs.cy[i].nm, gen.objs.cy[i].nm) * gen.objs.cy[i].d * gen.objs.cy[i].d / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					if (t_n[0] >= 0)
					{
						p = sum_vs(1, gen.scene.cdo, t_n[0], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
						if (len_vec(sum_vs(1, p, -1, gen.objs.cy[(int)gen.pix.z].cd)) <= sqrt(gen.objs.cy[(int)gen.pix.z].h * gen.objs.cy[(int)gen.pix.z].h / 4 + gen.objs.cy[(int)gen.pix.z].d * gen.objs.cy[(int)gen.pix.z].d / 4))
							fl = 2;
					}
					if (t_n[1] >= 0 && fl != 2)
					{
						p = sum_vs(1, gen.scene.cdo, t_n[1], sum_vs( 1, gen.scene.cdv, -1, gen.scene.cdo));
						if (len_vec(sum_vs(1, p, -1, gen.objs.cy[(int)gen.pix.z].cd)) <= sqrt(gen.objs.cy[(int)gen.pix.z].h * gen.objs.cy[(int)gen.pix.z].h / 4 + gen.objs.cy[(int)gen.pix.z].d * gen.objs.cy[(int)gen.pix.z].d / 4))
							fl = 3;
					}
					fl = belong_to_cyhead0(gen, i, &p, fl);
					fl = belong_to_cyhead1(gen, i, &p, fl);

					if (fl > 1 && len_vec(sum_vs(1, p, -1, gen.objs.c[gen.num_cam].cd)) <= len_vec(sum_vs(1, ptr, -1, gen.objs.c[gen.num_cam].cd)))
						return (1);
				}
			}
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}
