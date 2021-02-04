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

	(*i)++;
	k[0] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0), add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	k[2] = scalar_product_vecs(add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord), add_t_vecs( 1, gen->scene.coord_0, -1, gen->objects.sp[(int)gen->pix.z].coord)) - gen->objects.sp[(int)gen->pix.z].diam * gen->objects.sp[(int)gen->pix.z].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		fl = 0;
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
	if ((t[0] < 0 || t[1] <= t[0]))
		p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	else //if ((t[1] < 1 || t[0] < t[1]))
		p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));

	if (check_see_objs(*gen, p, (int)gen->pix.z) || (t[0] <= 1 && t[1] <= 1))
		fl = 0;

	/*(fl == 1 && z == 0) fun;
	(fl == 1 && z != 0) fun;
	(fl == 0 && z == 0) -5;
	(fl == 0 && z != 0) color;*/
	gen->color = (fl == 1) ? light_change_sp(*gen, p, (int)gen->pix.z) : gen->color;
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
	//printf("PL %f\n", t);
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
	//printf("PL %f\n", t);
	p = add_t_vecs(1, gen->objects.c[gen->num_cam].coord, t1, add_t_vecs( 1, gen->scene.coord_v, -1, gen->objects.c[gen->num_cam].coord));

	if (point_in_square(gen->objects.sq[(int)gen->pix.z], p))
	{
		if (!check_see_objs(*gen, p, 200 + (int)gen->pix.z))
			gen->color = light_change_sq(*gen, p, (int)gen->pix.z);
		//if (t != gen->color)
			//printf("Sq %f - last, %f - new\n", t, gen->color);
	}
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
	//printf("PL %f\n", t);
	p = add_t_vecs(1, gen->objects.c[gen->num_cam].coord, t1, add_t_vecs( 1, gen->scene.coord_v, -1, gen->objects.c[gen->num_cam].coord));

	if (point_in_triangle(gen->objects.tr[(int)gen->pix.z], p))
	{
		if (!check_see_objs(*gen, p, 300 + (int)gen->pix.z))
			gen->color = light_change_tr(*gen, p, (int)gen->pix.z);
		//if (t != gen->color)
			//printf("Sq %f - last, %f - new\n", t, gen->color);
	}
	gen->pix.z += 1;
	if (gen->objects.tr[(int)gen->pix.z].is == 1)
		gen->color = belong_to_triangle(gen, i);
	return (gen->color);
}


int		belong_to_cylinder(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p, p1, pa, pb;
	int fl;

	fl = 1;
	(*i)++;
	//gen->objects.cy[(int)gen->pix.z].coord
	//gen->objects.cy[(int)gen->pix.z].normal
	//gen->scene.coord_v
	//gen->scene.coord_0
	//add_t_vecs(1, p1, -1, p2)

	p1 = add_t_vecs(1, gen->objects.cy[(int)gen->pix.z].coord2, -1, gen->objects.cy[(int)gen->pix.z].coord); //P2-P1
	pa = add_t_vecs(scalar_product_vecs(pa, pa) / scalar_product_vecs(gen->scene.coord_v, pa), gen->scene.coord_v, -1, pa); //A
	pb = add_t_vecs(scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, p1) / scalar_product_vecs(gen->scene.coord_v, p1), gen->scene.coord_v, -1, gen->objects.cy[(int)gen->pix.z].coord); //B
	k[0] = scalar_product_vecs(pa, pa);
	k[1] = 2 * scalar_product_vecs(pa, pb);
	k[2] = scalar_product_vecs(pb, pb) - gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4;

	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		fl = 0;
	t[0] = (fl == 0) ? -5 : (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (fl == 0) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
	if (t[0] >  t[1])
	{
		k[2] = t[0];
		t[0] = t[1];
		t[1] = k[2];
	}

	if (t[0] > -0.001 && t[0] < 1.001 && fl > 0)
	{
		k[0] = (scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, p1) + t[0] * scalar_product_vecs(p1, p1)) / scalar_product_vecs(gen->scene.coord_v, p1);
		if (k[0] > 1)
		{
			p = add_t_vecs(1, gen->scene.coord_0, k[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
			fl = 2;
		}
	}
	if (t[1] > -0.001 && t[1] < 1.001  && fl > 0 && !(fl == 2 && t[0] <= t[1]))
	{
		k[1] = (scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, p1) + t[1] * scalar_product_vecs(p1, p1)) / scalar_product_vecs(gen->scene.coord_v, p1);
		if (k[1] > 1)
		{
			p = add_t_vecs(1, gen->scene.coord_0, k[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
			fl = 3;
		}
		else if (fl == 2)
			p = add_t_vecs(1, gen->scene.coord_0, k[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));

	}

	gen->color = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z) : gen->color;
	//gen->pix.z += 1;
	//if (gen->objects.tr[(int)gen->pix.z].is == 1)
		//gen->color = belong_to_cylinder(gen, i);
	return (gen->color);
	(void)k;
	(void)t;
	(void)p;
	(void)p1;
}

/*int		belong_to_cylinder(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p, p1;
	int fl;

	fl = 1;
	(*i)++;
	//gen->objects.cy[(int)gen->pix.z].coord
	//gen->objects.cy[(int)gen->pix.z].normal
	//gen->scene.coord_v
	//gen->scene.coord_0
	p = add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0); //VO
	p = vec_product_vecs(vec_product_vecs(p, gen->objects.cy[(int)gen->pix.z].normal), gen->objects.cy[(int)gen->pix.z].normal); //pnn
	k[0] = scalar_product_vecs(p, add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0)); //(p, VO)
	k[1] = scalar_product_vecs(p, add_t_vecs(1, gen->scene.coord_0, -1, gen->objects.cy[(int)gen->pix.z].coord)); //(p, OC)
	p = vec_product_vecs(vec_product_vecs(gen->scene.coord_0, gen->objects.cy[(int)gen->pix.z].normal), gen->objects.cy[(int)gen->pix.z].normal);
	k[1] -= scalar_product_vecs(p, add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0)); //- (Onn, VO)
	k[2] = scalar_product_vecs(p, add_t_vecs(1, gen->objects.cy[(int)gen->pix.z].coord, -1, gen->scene.coord_0)); //(Onn, CO)
	p = vec_product_vecs(vec_product_vecs(gen->objects.cy[(int)gen->pix.z].coord, gen->objects.cy[(int)gen->pix.z].normal), gen->objects.cy[(int)gen->pix.z].normal);
	k[1] += scalar_product_vecs(p, add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0)); //+ (Cnn, VO)
	k[2] -= scalar_product_vecs(p, add_t_vecs(1, gen->scene.coord_0, -1, gen->objects.cy[(int)gen->pix.z].coord)); //- (Cnn, OC)
	k[2] -= gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4 * scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, gen->objects.cy[(int)gen->pix.z].normal); //- d*d/4*(n,n)

	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		fl = 0;
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];

	if (t[0] > 0 && fl > 0)
	{
		printf("A\n");
		p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
		if (scalar_product_vecs(p, gen->objects.cy[(int)gen->pix.z].coord) * 4 - gen->objects.cy[(int)gen->pix.z].heig *gen->objects.cy[(int)gen->pix.z].heig + gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam <= 1)
			fl = 2;
	}
	if (t[1] > 0 && fl > 0 && !(fl == 2 && t[0] < t[1]))
	{
		printf("B\n");
		p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
		if (scalar_product_vecs(p, gen->objects.cy[(int)gen->pix.z].coord) * 4 - gen->objects.cy[(int)gen->pix.z].heig *gen->objects.cy[(int)gen->pix.z].heig + gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam < 0.1)
			fl = 3;
		else if (fl == 2)
			p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
	}

	gen->color = (fl > 1) ? light_change_cy(*gen, p, (int)gen->pix.z) : gen->color;
	//gen->pix.z += 1;
	//if (gen->objects.tr[(int)gen->pix.z].is == 1)
		//gen->color = belong_to_cylinder(gen, i);
	return (gen->color);
}*/

/*int		belong_to_cylinder(t_general *gen, int *i)
{
	float k[3];
	float t[2];
	t_vector p, p1;
	int fl;

	fl = 1;
	(*i)++;
	p = add_t_vecs(1, add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0), -1 * scalar_product_vecs(add_t_vecs(1, gen->scene.coord_v, -1, gen->scene.coord_0), gen->objects.cy[(int)gen->pix.z].normal), gen->objects.c[(int)gen->pix.z].normal);
	p1 = add_t_vecs(1, add_t_vecs(1, gen->scene.coord_0, -1, gen->objects.cy[(int)gen->pix.z].coord), -1 * scalar_product_vecs(add_t_vecs(1, gen->scene.coord_0, -1, gen->objects.cy[(int)gen->pix.z].coord), gen->objects.cy[(int)gen->pix.z].normal),gen->objects.cy[(int)gen->pix.z].normal);
	k[0] = scalar_product_vecs(p, p);
	k[1] = 2 * scalar_product_vecs(p, p1);
	k[2] = scalar_product_vecs(p1, p1) - gen->objects.cy[(int)gen->pix.z].diam * gen->objects.cy[(int)gen->pix.z].diam / 4;

	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		fl = 0;
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0

	p1 = add_t_vecs(1, gen->objects.cy[(int)gen->pix.z].coord, gen->objects.cy[(int)gen->pix.z].diam / 2 / sqrt(scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, gen->objects.cy[(int)gen->pix.z].normal)), gen->objects.cy[(int)gen->pix.z].normal); // вторая гран точка цилиндра
	if (t[0] > 1 && fl > 0)
	{
		p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
		if (lenght_vecs(vec_product_vecs(add_t_vecs(1, p, -1, gen->objects.cy[(int)gen->pix.z].coord), gen->objects.cy[(int)gen->pix.z].normal)) / lenght_vecs(gen->objects.cy[(int)gen->pix.z].normal) - gen->objects.cy[(int)gen->pix.z].diam / 2 < 0.1)
			fl = 2;
		//if ((scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, add_t_vecs(1, p , -1, gen->objects.cy[(int)gen->pix.z].coord)) > 0) && (scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, add_t_vecs(1, p , -1, p1)) < 0))
	}
	if (t[1] > 1 && fl > 0 && !(fl == 2 && t[0] <= t[1]))
	{
		p = add_t_vecs(1, gen->scene.coord_0, t[1], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
		if (lenght_vecs(vec_product_vecs(add_t_vecs(1, p, -1, gen->objects.cy[(int)gen->pix.z].coord), gen->objects.cy[(int)gen->pix.z].normal)) / lenght_vecs(gen->objects.cy[(int)gen->pix.z].normal) - gen->objects.cy[(int)gen->pix.z].diam / 2 < 0.1)
			fl = 3;
		else if (fl == 2)
			p = add_t_vecs(1, gen->scene.coord_0, t[0], add_t_vecs( 1, gen->scene.coord_v, -1, gen->scene.coord_0));
		//if ((scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, add_t_vecs(1, p , -1, gen->objects.cy[(int)gen->pix.z].coord)) > 0) && (scalar_product_vecs(gen->objects.cy[(int)gen->pix.z].normal, add_t_vecs(1, p , -1, p1)) < 0))
	}
	gen->color = (fl >= 2) ? light_change_cy(*gen, p, (int)gen->pix.z) : gen->color;
	//gen->pix.z += 1;
	//if (gen->objects.tr[(int)gen->pix.z].is == 1)
		//gen->color = belong_to_cylinder(gen, i);
	return (gen->color);
}*/
