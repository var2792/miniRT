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
/*
	if (num_ob > 199 && num_ob < 300) //square
		res = (res == 0) ? check_see_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res == 0) ? check_see_sp(num_l, -1, objects, p) : res;

	if (num_ob > 299 && num_ob < 400) //cylinder
		res = (res == 0) ? check_see_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res == 0) ? check_see_sp(num_l, -1, objects, p) : res;

	if (num_ob > 399 && num_ob < 500) //triangle
		res = (res == 0) ? check_see_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res == 0) ? check_see_sp(num_l, -1, objects, p) : res;
*/
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
			k[0] = scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0), add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
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
			ft_write_xyz(&p, 0, 0, 0);
			p = add_t_vecs(1, p, t, add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			if ((t > 1 && t < 200) && lenght_vecs(add_t_vecs(1, p, -1, gen.objects.c[gen.num_cam].coord)) <= lenght_vecs(add_t_vecs(1, ptr, -1, gen.objects.c[gen.num_cam].coord)))
					return (1);
		}
		i++;
	}
	return (0);
	(void) p;
	(void) ptr;
}

/*
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
			k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, gen.scene.coord_v, -1, gen.scene.coord_0));
			k[2] = scalar_product_vecs(add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord), add_t_vecs( 1, gen.scene.coord_0, -1, gen.objects.sp[i].coord)) - gen.objects.sp[i].diam * gen.objects.sp[i].diam / 4;
			t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
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
*/
