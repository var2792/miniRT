#include "belong_to_obj.h"

int	belong_to_sphere(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	fl = 1;
	/*if (gen->pix.x == 0 && gen->pix.y == 0)
		printf(" 0   0  %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 0 && gen->pix.y == 512)
		printf(" 0  512 %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 512 && gen->pix.y == 0)
		printf("512  0  %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);
	if (gen->pix.x == 512 && gen->pix.y == 512)
		printf("512 512 %f, %f, %f\n", gen->scene.coord_v.x, gen->scene.coord_v.y, gen->scene.coord_v.z);*/
	//1 842 183 // без проверки (первый if)
	//1 483 772 // C-O
	p = add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0);
	k[0] = lenght_vecs(vec_product_vecs(add_t_vecs(1, gen->objects.sp[(int)gen->pix.z].coord, -1, gen->scene.coord_0), p)) / lenght_vecs(p);
	if (k[0] <= gen->objects.sp[(int)gen->pix.z].diam * 2)
	{
		(*i)++;
		k[0] = scalar_product_vecs(p, p);
		k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), p);
		k[2] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord)) - gen->objects.sp[(int)gen->pix.z].diam * gen->objects.sp[(int)gen->pix.z].diam / 4;
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
			fl = 0;
		t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
		t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
		if ((t[0] < 0 || t[1] <= t[0]))
			p = add_t_vecs(1, gen->scene.coord_0, t[1], p);
		else //if ((t[1] < 1 || t[0] < t[1]))
			p = add_t_vecs(1, gen->scene.coord_0, t[0], p);

		if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
			fl = 0;

		/*(fl == 1 && z == 0) fun;
		(fl == 1 && z != 0) fun;
		(fl == 0 && z == 0) -5;
		(fl == 0 && z != 0) color;*/
		gen->color = (fl == 1) ? light_change_sp(*gen, p, (int)gen->pix.z) : gen->color;
	}
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

	(*i)++;

	t1 = scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.pl[(int)gen->pix.z].coord) - scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t2 = scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->scene.coord_v) - scalar_product_vecs(gen->objects.pl[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t = t1 / t2;
	ft_write_xyz(&p, 0, 0, 0);
	p = add_t_vecs(1, gen->objects.c[gen->num_cam].coord, t, add_t_vecs( 1, gen->scene.coord_v, -1, gen->objects.c[gen->num_cam].coord));

	if (!check_see_objs(*gen, p, 100 + (int)gen->pix.z) && (t > 1 && t < 200))
		gen->color = light_change_pl(*gen, p, (int)gen->pix.z);

	gen->pix.z += 1;
	if (gen->objects.pl[(int)gen->pix.z].is == 1)
		gen->color = belong_to_plane(gen, i);
	return (gen->color);
}

int		belong_to_square(t_general *gen, int *i)
{
	t_vector p;
	float t1, t2;

	(*i)++;

	t1 = scalar_product_vecs(gen->objects.sq[(int)gen->pix.z].normal, gen->objects.sq[(int)gen->pix.z].coord) - scalar_product_vecs(gen->objects.sq[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t2 = scalar_product_vecs(gen->objects.sq[(int)gen->pix.z].normal, gen->scene.coord_v) - scalar_product_vecs(gen->objects.sq[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t1 = t1 / t2;
	p = add_t_vecs(1, gen->objects.c[gen->num_cam].coord, t1, add_t_vecs( 1, gen->scene.coord_v, -1, gen->objects.c[gen->num_cam].coord));

	if (point_in_square(gen->objects.sq[(int)gen->pix.z], p))
		if (!check_see_objs(*gen, p, 200 + (int)gen->pix.z))
			gen->color = light_change_sq(*gen, p, (int)gen->pix.z);
	gen->pix.z += 1;
	if (gen->objects.sq[(int)gen->pix.z].is == 1)
		gen->color = belong_to_square(gen, i);
	return (gen->color);
}

int		belong_to_triangle(t_general *gen, int *i)
{
	t_vector p;
	float t1, t2;

	(*i)++;

	t1 = scalar_product_vecs(gen->objects.tr[(int)gen->pix.z].normal, gen->objects.tr[(int)gen->pix.z].coord_fir) - scalar_product_vecs(gen->objects.tr[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t2 = scalar_product_vecs(gen->objects.tr[(int)gen->pix.z].normal, gen->scene.coord_v) - scalar_product_vecs(gen->objects.tr[(int)gen->pix.z].normal, gen->objects.c[gen->num_cam].coord);
	t1 = t1 / t2;
	p = add_t_vecs(1, gen->objects.c[gen->num_cam].coord, t1, add_t_vecs( 1, gen->scene.coord_v, -1, gen->objects.c[gen->num_cam].coord));

	if (point_in_triangle(gen->objects.tr[(int)gen->pix.z], p))
		if (!check_see_objs(*gen, p, 300 + (int)gen->pix.z))
			gen->color = light_change_tr(*gen, p, (int)gen->pix.z);
	gen->pix.z += 1;
	if (gen->objects.tr[(int)gen->pix.z].is == 1)
		gen->color = belong_to_triangle(gen, i);
	return (gen->color);
}

int		belong_to_cylinder(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p;
	int fl;

	fl = 1;
	p = vec_product_vecs(add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0), gen->objects.cy[(int)gen->pix.z].normal);
	k[0] = fabs(scalar_product_vecs(add_t_vecs(1, gen->objects.cy[(int)gen->pix.z].coord, -1, gen->scene.coord_0), p) / lenght_vecs(p));
	if (k[0] <= gen->objects.cy[(int)gen->pix.z].diam / 2)
	{
		(*i)++;
		p = add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0);
		k[0] = scalar_product_vecs(vec_product_vecs(p, gen->objects.cy[(int)gen->pix.z].normal), vec_product_vecs(p, gen->objects.cy[(int)gen->pix.z].normal)); //(Vn,Vn)
		k[1] = 2 * scalar_product_vecs(vec_product_vecs(p, gen->objects.cy[(int)gen->pix.z].normal), add_t_vecs(1, vec_product_vecs(gen->scene.coord_0, gen->objects.cy[(int)gen->pix.z].normal), -1, vec_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, gen->objects.cy[(int)gen->pix.z].normal))); // 2(Vn,On-Cn)
		k[2] = scalar_product_vecs(add_t_vecs(1, vec_product_vecs(gen->scene.coord_0, gen->objects.cy[(int)gen->pix.z].normal), -1, vec_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, gen->objects.cy[(int)gen->pix.z].normal)), add_t_vecs(1, vec_product_vecs(gen->scene.coord_0, gen->objects.cy[(int)gen->pix.z].normal), -1, vec_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, gen->objects.cy[(int)gen->pix.z].normal))) - scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, gen->objects.cy[(int)gen->pix.z].normal) * gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4; //(On-Cn,On-Cn)-(n,n)*d*d/4
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		if (t[1] < 0 || k[0] == 0)
			fl = 0;
		t[0] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
		t[1] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
		/*if (t[0] > t[1]) //проверка что t[0] точно меньше t[1]
		{	k[2] = t[0];	t[0] = t[1];	t[1] = k[2];	}*/
		if (t[0] > 1 && fl > 0)
		{
			p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
			if (lenght_vecs(add_t_vecs(1, p, -1, gen->objects.cy[(int)gen->pix.z].coord)) <= sqrt(gen->objects.cy[(int)gen->pix.z].heig * gen->objects.cy[(int)gen->pix.z].heig / 4 + gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4))
				fl = 2;
		}
		if (t[1] > 1 && fl > 0 && fl != 2)
		{
			p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
			if (lenght_vecs(add_t_vecs(1, p, -1, gen->objects.cy[(int)gen->pix.z].coord)) <= sqrt(gen->objects.cy[(int)gen->pix.z].heig * gen->objects.cy[(int)gen->pix.z].heig / 4 + gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4))
				fl = 3;
		}

		if (check_see_objs(*gen, p, 400 + (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
			fl = 0;

		fl = belong_to_cyhead0(*gen, (int)gen->pix.z, &p, fl);
		fl = belong_to_cyhead1(*gen, (int)gen->pix.z, &p, fl);
		gen->color = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z, fl) : gen->color;
	}
	//gen->pix.z += 1;
	//if (gen->objects.tr[(int)gen->pix.z].is == 1)
		//gen->color = belong_to_cylinder(gen, i);
	return (gen->color);
	(void)k;
	(void)t;
	(void)p;
}

int		belong_to_cyhead0(t_general gen, int i, t_vector *pcy, int fl)
{
	t_vector p, h;
	float t1, t2;

	h = add_t_vecs(1, gen.objects.cy[i].coord, - gen.objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal)), gen.objects.cy[i].normal);
	//h = add_t_vecs(1, gen.objects.cy[i].coord, gen.objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal)), gen.objects.cy[i].normal);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t1 = scalar_product_vecs(gen.objects.cy[i].normal, h) - scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_0);
	t2 = scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_v) - scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_0);
	t1 = t1 / t2;
	p = add_t_vecs(1, gen.objects.c[gen.num_cam].coord, t1, add_t_vecs(1, gen.scene.coord_v, -1, gen.objects.c[gen.num_cam].coord));
	if (lenght_vecs(add_t_vecs(1, p, -1, h)) <= gen.objects.cy[i].diam / 2)
		if ((fl > 1 && lenght_vecs(add_t_vecs(1, p, -1, gen.scene.coord_0)) <= lenght_vecs(add_t_vecs(1, *pcy, -1, gen.scene.coord_0))) || fl < 2)
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

	//h = add_t_vecs(1, gen.objects.cy[i].coord, - gen.objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal)), gen.objects.cy[i].normal);
	h = add_t_vecs(1, gen.objects.cy[i].coord, gen.objects.cy[i].heig / 2 / sqrt(scalar_product_vecs(gen.objects.cy[i].normal, gen.objects.cy[i].normal)), gen.objects.cy[i].normal);

	//printf("Cy %f %f %f\n", h.x, h.y, h.z);

	t1 = scalar_product_vecs(gen.objects.cy[i].normal, h) - scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_0);
	t2 = scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_v) - scalar_product_vecs(gen.objects.cy[i].normal, gen.scene.coord_0);
	t1 = t1 / t2;
	p = add_t_vecs(1, gen.objects.c[gen.num_cam].coord, t1, add_t_vecs(1, gen.scene.coord_v, -1, gen.objects.c[gen.num_cam].coord));
	if (lenght_vecs(add_t_vecs(1, p, -1, h)) <= gen.objects.cy[i].diam / 2)
		if ((fl > 1 && lenght_vecs(add_t_vecs(1, p, -1, gen.scene.coord_0)) <= lenght_vecs(add_t_vecs(1, *pcy, -1, gen.scene.coord_0))) || fl < 2)
		{
			pcy->x = p.x;
			pcy->y = p.y;
			pcy->z = p.z;
			return (4);
		}
	return (fl);
	//return (gen->color);
}
