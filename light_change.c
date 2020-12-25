#include "light_change.h"

int		check_shadow(int num_l, int num_sp, t_objscene objects, t_canvas scene, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	/*float k[3];
	float t[2];
	t_vector temp;
	int i;
	int len;

	i = 1; // заходит в несуществ сферы и в текущюю???
	while (objects.sp[i].is == 1)
	{
		//printf("%i\n", objects.sp[i].is);
		if (i != num_sp)
		{
		k[0] = scalar_product_vecs(p, p);
		k[1] = 2 * scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
		k[2] = scalar_product_vecs(add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs( 1, objects.l[num_l].coord, -1, objects.sp[i].coord)) - objects.sp[i].diam * objects.sp[i].diam / 4;
		t[1] = k[1] * k[1] - 4 * k[0] * k[2];
		//printf("k1 = %f,\tk2 = %f,\tk3 = %f,\tD = %f\n", k[0], k[1], k[2], t[1]);
		if (!(t[1] < -0.01 || (k[0] == 0 && k[1] == 0)))
		{
			t[0] = (-k[1] + sqrt(t[1]))/ 2 / k[0];
			t[1] = (t[0] < 1 && t[1] < 0.01 && t[1] > -0.01) ? -5 : (-k[1] - sqrt(t[1]))/ 2 / k[0]; //если D == 0 и t[0] < 0
			ft_write_xyz(&temp, 0, 0, 0);
			if ((t[0] < 0 || t[1] <= t[0]))
				temp = add_t_vecs(1, objects.l[num_l].coord, t[1], add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			if ((t[1] < 0 || t[0] < t[1]))
				temp = add_t_vecs(1, objects.l[num_l].coord, t[0], add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			if ((len = lenght_vecs(add_t_vecs( 1, temp, -1, objects.l[num_l].coord))) > 0 && len < lenght_vecs(add_t_vecs( 1, p, -1, objects.l[num_l].coord)))
				return (0);
		}
		}
		i++;
	}*/

	return (1);
	(void)scene;
	(void)objects;
	(void)p;
	(void)num_l;
	(void)num_sp;
}

float	light_change_sp(t_objscene objects, t_canvas scene, t_vector p, int i)
{
	float bright;
	float res_br;
	t_vector lig;
	t_vector norm;
	int num_l;

	res_br = objects.a.rat_amlig;
	num_l = 0;
	while (objects.l[num_l].is)
	{
		norm = add_t_vecs(-1 / lenght_vecs(add_t_vecs(1, p, -1, objects.sp[i].coord)), p, 1 / lenght_vecs(add_t_vecs( 1, p, -1, objects.sp[i].coord)), objects.sp[i].coord);
		lig = add_t_vecs( 1, p, -1, objects.l[num_l].coord);
		if ((bright = scalar_product_vecs(norm, lig) / lenght_vecs(lig)) < 0)
			bright = 0;
		//if (i == 0)
			res_br += objects.l[num_l].brirat * bright * check_shadow(num_l, i, objects, scene, p);
		//else
			//res_br += objects.l[num_l].brirat * bright;
		/*norm = add_t_vecs(2 * scalar_product_vecs(norm, lig), norm, -1, lig);

		if ((bright = scalar_product_vecs(norm, scene.coord_v) / lenght_vecs(lig) / lenght_vecs(scene.coord_v)) < 0)
			bright = 0;
		res_br += objects.l[num_l].brirat * exp(9 * log(bright)); //зеркальность ?- как то так
		*/
		objects.l[0].color.x = (num_l == 0) ? objects.l[num_l].brirat * objects.l[num_l].color.x * res_br
		: objects.l[0].color.x + objects.l[num_l].brirat * objects.l[num_l].color.x * res_br;
		objects.l[0].color.y = (num_l == 0) ? objects.l[num_l].brirat * objects.l[num_l].color.y * res_br
		: objects.l[0].color.y + objects.l[num_l].brirat * objects.l[num_l].color.y * res_br;
		objects.l[0].color.z = (num_l == 0) ? objects.l[num_l].brirat * objects.l[num_l].color.z * res_br
		: objects.l[0].color.z + objects.l[num_l].brirat * objects.l[num_l].color.z * res_br;
		num_l++;
	}
	num_l--;
	if (res_br > 1)
		res_br = 1;
	objects.sp[i].color.x = (0.333 * objects.sp[i].color.x + 0.333 * objects.l[0].color.x + 0.333 * objects.a.color.x) * res_br;
	objects.sp[i].color.y = (0.333 * objects.sp[i].color.y + 0.333 * objects.l[0].color.y + 0.333 * objects.a.color.y) * res_br;
	objects.sp[i].color.z = (0.333 * objects.sp[i].color.z + 0.333 * objects.l[0].color.z + 0.333 * objects.a.color.z) * res_br;
	objects.sp[i].color.x = (objects.sp[i].color.x > 255) ? 255 : objects.sp[i].color.x;
	objects.sp[i].color.y = (objects.sp[i].color.y > 255) ? 255 : objects.sp[i].color.y;
	objects.sp[i].color.z = (objects.sp[i].color.z > 255) ? 255 : objects.sp[i].color.z;
	/*objects.sp[i].color.x *= res_br;
	objects.sp[i].color.y *= res_br;		//не цветное освещение
	objects.sp[i].color.z *= res_br;*/
	return (ft_colorvec_unsint(1, objects.sp[i].color));
	(void)scene;
}
