#include "../incs/funct_def.h"

t_vector		ft_write_xyz(t_vector *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (*vec);
}

unsigned int	ft_colorvec_unsint(float br, t_vector vec)
{
	unsigned int num;
	unsigned int r[2];
	unsigned int g[2];
	unsigned int b[2];

	r[0] = (unsigned int)(vec.x) / 16;
	r[1] = (unsigned int)(vec.x) % 16;
	g[0] = (unsigned int)(vec.y) / 16;
	g[1] = (unsigned int)(vec.y) % 16;
	b[0] = (unsigned int)(vec.z) / 16;
	b[1] = (unsigned int)(vec.z) % 16;
	/*printf("r[0] = %u, r[1] = %u\n", r[0], r[1]);
	printf("g[0] = %u, g[1] = %u\n", g[0], g[1]);
	printf("b[0] = %u, b[1] = %u\n", b[0], b[1]);*/
	num = (r[0] * 16 + r[1]) * 16 * 16 * 16 * 16 + (g[0] * 16 + g[1]) * 16 * 16 + b[0] * 16 + b[1];
	return (br * num);
}
