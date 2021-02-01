#include "square_fun.h"

t_vector	find_apex_sq(t_square sq, t_vector *rotmat, t_vector p)
{
	t_vector tp;
	float t;

	tp = multiply_mat_vec(rotmat, p);
	t = sqrt(3 * sq.size * sq.size / 4 / scalar_product_vecs(tp, tp));
	tp = add_t_vecs(1, sq.coord, t, tp);
	return (tp);
}

void	find_point_sq(t_general gen, t_vector (*P)[])
{
	t_vector pnul, *rotmat;

	ft_write_xyz(&pnul, 0, 0, 0);
	rotmat = rotation_matrix(gen.objects.sq[0].normal, gen.objects.orig_cam, pnul);

	ft_write_xyz(&pnul, 1, 1, 1);
	(*P)[0] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, 1, 1, -1);
	(*P)[1] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, 1, -1, -1);
	(*P)[2] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, 1, -1, 1);
	(*P)[3] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, -1, 1, 1);
	(*P)[4] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, -1, 1, -1);
	(*P)[5] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, -1, -1, -1);
	(*P)[6] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);

	ft_write_xyz(&pnul, -1, -1, 1);
	(*P)[7] = find_apex_sq(gen.objects.sq[0], rotmat, pnul);
	free(rotmat);
}

t_vector	convert_pinv(t_general gen, t_vector p)
{
	t_vector v, pix;

	//printf("%f %f %f\n", p.x, p.y, p.z); // +
	v.x = p.x * gen.scene.viewport.z / p.z;
	v.y = p.y * gen.scene.viewport.z / p.z;
	//printf("%f %f\n", v.x, v.y); // +
	pix.x = trunc(gen.objects.r.x / 2 + v.x * gen.objects.r.x / gen.scene.viewport.x);
	pix.y = trunc(gen.objects.r.y / 2 - v.y * gen.objects.r.y / gen.scene.viewport.y);
	pix.z = trunc(gen.scene.viewport.z);
	//printf("%f %f %f\n", pix.x, pix.y, pix.z);
	return (pix);
}
