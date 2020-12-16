# include "light_change.h"

t_vector raz_vecs(t_vector vec1, t_vector vec2)
{
	t_vector raz;

	raz.x = vec1.x - vec2.x;
	raz.y = vec1.y - vec2.y;
	raz.z = vec1.z - vec2.z;
	return (raz);
}

t_vector add_t_vecs(float t1, t_vector vec1, float t2, t_vector vec2)
{
	t_vector raz;

	raz.x = t1 * vec1.x + t2 *vec2.x;
	raz.y = t1 * vec1.y + t2 *vec2.y;
	raz.z = t1 * vec1.z + t2 *vec2.z;
	return (raz);
}

float	scalar_product_vecs(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float	lenght_vecs(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
