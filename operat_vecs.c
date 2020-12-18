# include "light_change.h"

t_vector	multiply_mat_vec(t_vector mat[], t_vector vec)
{
	t_vector res;

	res.x = vec.x * mat[0].x + vec.y * mat[1].x + vec.z * mat[2].x + mat[3].x;
	res.y = vec.x * mat[0].y + vec.y * mat[1].y + vec.z * mat[2].y + mat[3].y;
	res.z = vec.x * mat[0].z + vec.y * mat[1].z + vec.z * mat[2].z + mat[3].z;
	return(res);
}

t_vector	rotation_multiply(t_objscene objects, t_vector vec)
{
	t_vector res;
	t_vector mat[4];
	float T[3];

	ft_write_xyz(&(mat[0]), objects.c[0].normal.x, 0, objects.c[0].normal.z);
	T[0] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam));
	ft_write_xyz(&(mat[0]), objects.c[0].normal.x, objects.c[0].normal.y, 0);
	T[1] = (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam));
	ft_write_xyz(&(mat[0]), 0, objects.c[0].normal.y, objects.c[0].normal.z);
	T[2] = (objects.c[0].normal.z < 0) ? (lenght_vecs(mat[0]) < 0.01) ? 0 : acos(scalar_product_vecs(mat[0], objects.orig_cam) / lenght_vecs(mat[0]) / lenght_vecs(objects.orig_cam)) : 0;
	if (vec.x < 0.00000001 && vec.x > -0.00000001 && vec.y < 0.00000001 && vec.y > -0.00000001)
		printf("T[0] = %f, T[1] = %f, T[2]= %f\n", T[0] * 180 / 3.1415925, T[1] * 180 / 3.1415925, T[2]);

	ft_write_xyz(&(mat[0]), cos(T[1]) * cos(T[2]), -cos(T[1]) * sin(T[2]), sin(T[1]));
	ft_write_xyz(&(mat[1]), -sin(T[0]) * cos(T[2]) * sin(T[1]) + cos(T[0]) * sin(T[2]), cos(T[0]) * cos(T[2]) + sin(T[0]) * sin(T[1]) * sin(T[2]), -cos(T[1]) * sin(T[0]));
	ft_write_xyz(&(mat[2]), cos(T[0]) * cos(T[2]) * sin(T[1]) + sin(T[0]) * sin(T[2]), sin(T[0]) * cos(T[2]) - cos(T[0]) * sin(T[1]) * sin(T[2]), cos(T[1]) * cos(T[0]));

	/*ft_write_xyz(&(mat[0]), cos(T[1]) * cos(T[2]), -cos(T[1]) * sin(T[2]), sin(T[1]));
	ft_write_xyz(&(mat[1]), sin(T[0]) * cos(T[2]) * sin(T[1]) + cos(T[0]) * sin(T[2]), cos(T[0]) * cos(T[2]) - sin(T[0]) * sin(T[1]) * sin(T[2]), -cos(T[1]) * sin(T[0]));
	ft_write_xyz(&(mat[2]), -cos(T[0]) * cos(T[2]) * sin(T[1]) + sin(T[0]) * sin(T[2]), sin(T[0]) * cos(T[2]) + cos(T[0]) * sin(T[1]) * sin(T[2]), cos(T[1]) * cos(T[0]));

	ft_write_xyz(&(mat[0]), cos(T[2]) * cos(T[1]) - cos(T[0]) * sin(T[2]) * sin(T[1]), sin(T[2]) * cos(T[1]) + cos(T[0]) * cos(T[2]) * sin(T[1]), sin(T[1]) * sin(T[0]));
	ft_write_xyz(&(mat[1]), -cos(T[2]) * sin(T[1]) - cos(T[0]) * sin(T[2]) * cos(T[1]), -sin(T[2]) * sin(T[1]) + cos(T[0]) * cos(T[2]) * cos(T[1]), cos(T[1]) * sin(T[0]));
	ft_write_xyz(&(mat[2]), sin(T[2]) * sin(T[0]), -cos(T[2]) * sin(T[0]), cos(T[0]));*/
	mat[3] = objects.c[0].coord;//add_t_vecs(2, objects.c[0].coord, -1, objects.c[0].coord);
	res = multiply_mat_vec(mat, vec);
	return (res);
}

t_vector	add_t_vecs(float t1, t_vector vec1, float t2, t_vector vec2)
{
	t_vector raz;

	raz.x = t1 * vec1.x + t2 *vec2.x;
	raz.y = t1 * vec1.y + t2 *vec2.y;
	raz.z = t1 * vec1.z + t2 *vec2.z;
	return (raz);
}

float		scalar_product_vecs(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

float		lenght_vecs(t_vector vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}
