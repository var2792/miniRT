#include "drawing_objs.h"

int		belong_to_square(t_general *gen, int *i)
{
	t_vector P[8];

	/*gen->scene.cdv.x = (gen->pix.x - gen->objs.r.x / 2) * gen->scene.viewport.x / gen->objs.r.x;
	gen->scene.cdv.y = (gen->objs.r.y / 2 - gen->pix.y) * gen->scene.viewport.y / gen->objs.r.y;
	gen->scene.cdv.z = gen->scene.viewport.z;

	gen->scene.cdv = mult_m_v(gen->scene.rotmat, gen->scene.cdv);*/
	(*i)++;
	find_point_sq(*gen, &P);
	/*printf("%f, %f, %f\n", P[0].x, P[0].y, P[0].z);
	printf("%f, %f, %f\n", P[4].x, P[4].y, P[4].z);
	printf("%f, %f, %f\n", P[3].x, P[3].y, P[3].z);
	printf("%f, %f, %f\n", P[7].x, P[7].y, P[7].z);*/
	draw_side_sq(gen, P);

	return (gen->cl);
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
