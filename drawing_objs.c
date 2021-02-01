#include "drawing_objs.h"

int		belong_to_square(t_general *gen, int *i)
{
	t_vector P[8];

	/*gen->scene.coord_v.x = (gen->pix.x - gen->objects.r.x / 2) * gen->scene.viewport.x / gen->objects.r.x;
	gen->scene.coord_v.y = (gen->objects.r.y / 2 - gen->pix.y) * gen->scene.viewport.y / gen->objects.r.y;
	gen->scene.coord_v.z = gen->scene.viewport.z;

	gen->scene.coord_v = multiply_mat_vec(gen->scene.rotmat, gen->scene.coord_v);*/
	(*i)++;
	find_point_sq(*gen, &P);
	/*printf("%f, %f, %f\n", P[0].x, P[0].y, P[0].z);
	printf("%f, %f, %f\n", P[4].x, P[4].y, P[4].z);
	printf("%f, %f, %f\n", P[3].x, P[3].y, P[3].z);
	printf("%f, %f, %f\n", P[7].x, P[7].y, P[7].z);*/
	draw_side_sq(gen, P);

	return (gen->color);
}

int		belong_to_cylinder(t_objscene objects, t_scene scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}

int		belong_to_triangle(t_objscene objects, t_scene scene, t_vector pix)
{
	(void)objects;
	(void)scene;
	(void)pix;
	return (1);
}
