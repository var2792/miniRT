#include "check_shadows.h"

float		check_shadow(int num_l, int num_ob, t_objscene objects, t_vector p)
{
	float res;
	
	res = 1;
	if (num_ob > -1 && num_ob < 100) //sphere
		res = check_shadow_sp(num_l, num_ob, objects, p);
	else
		res = check_shadow_sp(num_l, -1, objects, p);
/*
	if (num_ob > 99 && num_ob < 200) //plane а она вообще существует?
		res = (res > 0.5) ? check_shadow_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res > 0.5) ? check_shadow_sp(num_l, -1, objects, p) : res;
	
	if (num_ob > 199 && num_ob < 300) //square
		res = (res > 0.5) ? check_shadow_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res > 0.5) ? check_shadow_sp(num_l, -1, objects, p) : res;
		
	if (num_ob > 299 && num_ob < 400) //cylinder
		res = (res > 0.5) ? check_shadow_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res > 0.5) ? check_shadow_sp(num_l, -1, objects, p) : res;
		
	if (num_ob > 399 && num_ob < 500) //triangle
		res = (res > 0.5) ? check_shadow_sp(num_l, (int)(num_ob % 100), objects, p) : res;
	else
		res = (res > 0.5) ? check_shadow_sp(num_l, -1, objects, p) : res;
*/
	return (res);
}

float		check_shadow_sp(int num_l, int num_sp, t_objscene objects, t_vector p)
{ // на бодобии этой функции сделать видимость/наложение сфер
	float k[3];
	float t_n[2];
	int i;

	i = 0;
	while (objects.sp[i].is)
	{
		if (i != num_sp)
		{
			k[0] = scalar_product_vecs(add_t_vecs(1, p, -1, objects.l[num_l].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			k[1] = 2 * scalar_product_vecs(add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs( 1, p, -1, objects.l[num_l].coord));
			k[2] = scalar_product_vecs(add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord), add_t_vecs(1, objects.l[num_l].coord, -1, objects.sp[i].coord)) - objects.sp[i].diam * objects.sp[i].diam / 4;
			t_n[1] = k[1] * k[1] - 4 * k[0] * k[2];
			if (!(t_n[1] < 0 || (k[0] == 0 && k[1] == 0)))
			{
				t_n[0] = (-k[1] + sqrt(t_n[1]))/ 2 / k[0];
				t_n[1] = (-k[1] - sqrt(t_n[1]))/ 2 / k[0];
				if ((t_n[0] > 0 && t_n[0] < 1) || (t_n[1] > 0 && t_n[1] < 1))
					return (0);
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

