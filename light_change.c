#include "light_change.h"

float		check_shadow(int num_l, int num_sp, t_objscene objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t[2];
	float t_n[2];
	int i;

	i = 0;
	k[0] = scalar_product_vecs(add_t_vecs( 1, p, -1, objects.l[num_l].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
	k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[num_sp].coord), add_t_vecs( 1, add_t_vecs( 1, p, -1, objects.l[num_l].coord), -1, objects.l[num_l].coord));
	k[2] = scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[num_sp].coord), add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[num_sp].coord)) - objects.sp[num_sp].diam * objects.sp[num_sp].diam / 4;
	t[1] = k[1] * k[1] - 4 * k[0] * k[2];
	if (t[1] < 0 || (k[0] == 0 && k[1] == 0))
		return (1);
	t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
	t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0];
	if (t[0] > t[1])
		t[0] = t[1];
	while (objects.sp[i].is)
	{
		if (i != num_sp)
		{
			k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs(1, add_t_vecs( 1, p, -1, objects.l[num_l].coord), -1, objects.l[num_l].coord));
			k[2] = scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord)) - objects.sp[i].diam * objects.sp[i].diam / 4;
			t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t_n[1] < -0.01 || (k[0] == 0 && k[1] == 0)))
			{
				t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
				t_n[1] = (t_n[0] < 1 && t_n[1] < 0.01 && t_n[1] > -0.01) ? -5 : (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
				if ((t_n[0] > 0 && t_n[0] < t[0]) || (t_n[1] > 0 && t_n[1] < t[0]))
				{
					return (0.2);
				}
			}
		}
		i++;
	}
	return (1);
	(void)objects;
	(void)p;
	(void)num_l;
	(void)num_sp;
}

float	light_change_sp(t_general gen, t_vector p, int i)
{
	float bright;
	float res_br;
	t_vector lig;
	t_vector norm;
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
		//else
			//res_br += objects.l[num_l].brirat * bright;
		/*norm = add_t_vecs(2 * scalar_product_vecs(norm, lig), norm, -1, lig);

		if ((bright = scalar_product_vecs(norm, scene.coord_v) / lenght_vecs(lig) / lenght_vecs(scene.coord_v)) < 0)
			bright = 0;
		res_br += objects.l[num_l].brirat * exp(9 * log(bright)); //зеркальность ?- как то так
		*/
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
	gen.objects.sp[i].color.x = (0.333 * gen.objects.sp[i].color.x + 0.333 * gen.objects.l[0].color.x + 0.333 * gen.objects.a.color.x) * res_br;
	gen.objects.sp[i].color.y = (0.333 * gen.objects.sp[i].color.y + 0.333 * gen.objects.l[0].color.y + 0.333 * gen.objects.a.color.y) * res_br;
	gen.objects.sp[i].color.z = (0.333 * gen.objects.sp[i].color.z + 0.333 * gen.objects.l[0].color.z + 0.333 * gen.objects.a.color.z) * res_br;
	gen.objects.sp[i].color.x = (gen.objects.sp[i].color.x > 255) ? 255 : gen.objects.sp[i].color.x;
	gen.objects.sp[i].color.y = (gen.objects.sp[i].color.y > 255) ? 255 : gen.objects.sp[i].color.y;
	gen.objects.sp[i].color.z = (gen.objects.sp[i].color.z > 255) ? 255 : gen.objects.sp[i].color.z;
	/*objects.sp[i].color.x *= res_br;
	objects.sp[i].color.y *= res_br;		//не цветное освещение
	objects.sp[i].color.z *= res_br;*/
	return (ft_colorvec_unsint(1, gen.objects.sp[i].color));
}
