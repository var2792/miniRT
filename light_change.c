#include "light_change.h"

float light_change_sp(t_objscene objects, t_vector p)
{
	float bright;
	t_vector lig;
	t_vector norm;
	norm = add_t_vecs(-1 / lenght_vecs(raz_vecs(p, objects.sp.coord)), p, 1 / lenght_vecs(raz_vecs(p, objects.sp.coord)), objects.sp.coord);
	//printf("%f %f %f\n", lenght_vecs(norm), norm.y, norm.z);
	lig = raz_vecs(p, objects.l.coord);
	bright = scalar_product_vecs(norm, lig) / lenght_vecs(lig);
	if (bright < 0)
		bright = 0;
	//printf("-> %f %f %f\n", objects.sp.color.x, objects.sp.color.y, objects.sp.color.z);
	bright = objects.a.rat_amlig + objects.l.brirat * bright;
	if (bright > 1)
		bright = 1;
	//printf("---> %f\n", bright);
	objects.sp.color.x *= bright;
	objects.sp.color.y *= bright;
	objects.sp.color.z *= bright;
	//printf("-----> %f %f %f\n", objects.sp.color.x, objects.sp.color.y, objects.sp.color.z);
	return (ft_colorvec_unsint(1, objects.sp.color));
}
