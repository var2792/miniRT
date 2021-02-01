#include "operat_vecs.h"

t_vector	multiply_mat_vec(t_vector *mat, t_vector vec)
{
	t_vector res;

	res.x = vec.x * mat[0].x + vec.y * mat[1].x + vec.z * mat[2].x + mat[3].x;
	res.y = vec.x * mat[0].y + vec.y * mat[1].y + vec.z * mat[2].y + mat[3].y;
	res.z = vec.x * mat[0].z + vec.y * mat[1].z + vec.z * mat[2].z + mat[3].z;
	return(res);
}

t_vector	add_t_vecs(float t1, t_vector vec1, float t2, t_vector vec2)
{
	t_vector raz;

	raz.x = t1 * vec1.x + t2 *vec2.x;
	raz.y = t1 * vec1.y + t2 *vec2.y;
	raz.z = t1 * vec1.z + t2 *vec2.z;
	return (raz);
}

t_vector		vec_product_vecs(t_vector vec1, t_vector vec2)
{
	t_vector res;

	res.x = vec1.y * vec2.z - vec1.z * vec2.y;
	res.y = -vec1.x * vec2.z + vec1.z * vec2.x;
	res.z = vec1.x * vec2.y - vec1.z * vec2.x;
	return (res);
}

float		scalar_product_vecs(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float		lenght_vecs(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
