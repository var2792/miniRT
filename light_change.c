#include "light_change.h"

float light_change_sp(t_objscene objects, t_vector p, int i)
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
		res_br += objects.l[num_l].brirat * bright;
		num_l++;
	}
	if (res_br > 1)
		res_br = 1;
	objects.sp[i].color.x *= res_br;
	objects.sp[i].color.y *= res_br;
	objects.sp[i].color.z *= res_br;
	return (ft_colorvec_unsint(1, objects.sp[i].color));
}
