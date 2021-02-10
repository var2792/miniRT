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
	while (gen.objects.sp[i].is)
	{
		if (i != num_sp)
		{
			p = add_t_vecs(1, gen.scene.coord_v, -1, gen.scene.coord_0);
			k[0] = lenght_vecs(vec_product_vecs(add_t_vecs(1, gen.objects.sp[i].coord, -1, gen.scene.coord_0), p)) / lenght_vecs(p);
			if (k[0] <= gen.objects.sp[i].diam * 2)
			{
				k[0] = scalar_product_vecs(p, p);
				k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), p);
				k[2] = scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord)) - gen.objects.sp[i].diam * gen.objects.sp[i].diam / 4;
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (t_n[0] < 1 && t_n[1] < 0.01 && t_n[1] > -0.01) ? -5 : (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					if ((t_n[0] < 0 || t_n[1] <= t_n[0]))
						p = add_t_vecs(1, gen.scene.coord_0, t_n[1], add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
					else
						p = add_t_vecs(1, gen.scene.coord_0, t_n[0], add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));

					if (lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
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
	while (gen.objects.pl[i].is)
	{
		if (i != num_pl)
		{
			t1 = scalar_product_vecs(gen.objects.pl[i].normal, gen.objects.pl[i].coord) - scalar_product_vecs(gen.objects.pl[i].normal, gen.objects.c[gen.num_cam].coord);
			t2 = scalar_product_vecs(gen.objects.pl[i].normal, gen.scene.coord_v) - scalar_product_vecs(gen.objects.pl[i].normal, gen.objects.c[gen.num_cam].coord);
			t = t1 / t2;
			//printf("PL %f\n", t);
			p = add_t_vecs(1, gen.scene.coord_0, t, add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			if ((t >= 1 && t < 200) && lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
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
	while (gen.objects.sq[i].is)
	{
		if (i != num_sq)
		{
			t1 = scalar_product_vecs(gen.objects.sq[i].normal, gen.objects.sq[i].coord) - scalar_product_vecs(gen.objects.sq[i].normal, gen.objects.c[gen.num_cam].coord);
			t2 = scalar_product_vecs(gen.objects.sq[i].normal, gen.scene.coord_v) - scalar_product_vecs(gen.objects.sq[i].normal, gen.objects.c[gen.num_cam].coord);
			t1 = t1 / t2;
	//printf("PL %f\n", t);
			p = add_t_vecs(1, gen.scene.coord_0, t1, add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			if (point_in_square(gen.objects.sq[i], p))
				if (lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
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
	while (gen.objects.tr[i].is)
	{
		if (i != num_tr)
		{
			t1 = scalar_product_vecs(gen.objects.tr[i].normal, gen.objects.tr[i].coord_fir) - scalar_product_vecs(gen.objects.tr[i].normal, gen.objects.c[gen.num_cam].coord);
			t2 = scalar_product_vecs(gen.objects.tr[i].normal, gen.scene.coord_v) - scalar_product_vecs(gen.objects.tr[i].normal, gen.objects.c[gen.num_cam].coord);
			t1 = t1 / t2;
	//printf("PL %f\n", t);
			p = add_t_vecs(1, gen.scene.coord_0, t1, add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			if (point_in_triangle(gen.objects.tr[i], p))
				if (lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
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
	while (gen.objects.cy[i].is)
	{
		if (i != num_cy)
		{
			p = vec_product_vecs(add_t_vecs(1, gen.scene.coord_v, -1, gen.scene.coord_0), gen.objects.cy[i].normal);
			k[0] = fabs(scalar_product_vecs(add_t_vecs(1, gen.objects.cy[i].coord, -1, gen.scene.coord_0), p) / lenght_vecs(p));
			if (k[0] <= gen.objects.cy[i].diam / 2)
			{
				fl = 1;
				p = add_t_vecs(1, gen.scene.coord_v, -1, gen.scene.coord_0);
				k[0] = scalar_product_vecs(vec_product_vecs(p, gen.objects.cy[i].normal), vec_product_vecs(p, gen.objects.cy[i].normal)); //(Vn,Vn)
				k[1] = 2 * scalar_product_vecs(vec_product_vecs(p, gen.objects.cy[i].normal), add_t_vecs(1, vec_product_vecs(gen.scene.coord_0, gen.objects.cy[i].normal), -1, vec_product_vecs(gen.objects.cy[i].coord, gen.objects.cy[i].normal))); // 2(Vn,On-Cn)
				k[2] = scalar_product_vecs(add_t_vecs(1, vec_product_vecs(gen.scene.coord_0, gen.objects.cy[i].normal), -1, vec_product_vecs(gen.objects.cy[i].coord, gen.objects.cy[i].normal)), add_t_vecs(1, vec_product_vecs(gen.scene.coord_0, gen.objects.cy[i].normal), -1, vec_product_vecs(gen.objects.cy[i].coord, gen.objects.cy[i].normal))) - scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal) * gen.objects.cy[i].diam * gen.objects.cy[i].diam / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
				t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
				if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
				{
					t_n[0] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
					t_n[1] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
					if (t_n[0] >= 0)
					{
						p = add_t_vecs(1, gen.scene.coord_0, t_n[0], add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
						if (lenght_vecs(add_t_vecs(1, p, -1, gen.objects.cy[(int)gen.pix.z].coord)) <= sqrt(gen.objects.cy[(int)gen.pix.z].heig * gen.objects.cy[(int)gen.pix.z].heig / 4 + gen.objects.cy[(int)gen.pix.z].diam * gen.objects.cy[(int)gen.pix.z].diam / 4))
							fl = 2;
					}
					if (t_n[1] >= 0 && fl != 2)
					{
						p = add_t_vecs(1, gen.scene.coord_0, t_n[1], add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
						if (lenght_vecs(add_t_vecs(1, p, -1, gen.objects.cy[(int)gen.pix.z].coord)) <= sqrt(gen.objects.cy[(int)gen.pix.z].heig * gen.objects.cy[(int)gen.pix.z].heig / 4 + gen.objects.cy[(int)gen.pix.z].diam * gen.objects.cy[(int)gen.pix.z].diam / 4))
							fl = 3;
					}
					fl = belong_to_cyhead0(gen, i, &p, fl);
					fl = belong_to_cyhead1(gen, i, &p, fl);

					if (fl > 1 && lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
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
