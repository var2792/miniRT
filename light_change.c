#include "light_change.h"

float light_change(t_objscene objects, t_vector p, int fl)
{
	float bright;
	t_vector lig;
	t_vector norm;
	norm = add_t_vecs(1 / lenght_vecs(raz_vecs(p, objects.sp.coord)), p, -1 / lenght_vecs(raz_vecs(p, objects.sp.coord)), objects.sp.coord);
	//printf("%f %f %f\n", lenght_vecs(norm), norm.y, norm.z);
	lig = raz_vecs(p, objects.l.coord);
	bright = scalar_product_vecs(norm, lig) / lenght_vecs(lig);
	if (bright < 0 || !fl)
		return (1);
	//printf("--> %f\n", bright);
	bright = objects.l.brirat * bright;
	objects.sp.color.z *= bright;
	return (ft_colorvec_unsint(1, objects.sp.color));
}
