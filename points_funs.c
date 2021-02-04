#include "points_funs.h"

t_vector	find_apex_sq(t_square sq, t_vector *rotmat, t_vector p)
{
	t_vector tp;
	float t;

	tp = multiply_mat_vec(rotmat, p);
	t = sqrt(sq.size * sq.size / 2 / scalar_product_vecs(tp, tp));
	tp = add_t_vecs(1, sq.coord, t, tp);
	return (tp);
}

void	find_point_sq(t_square sq, t_vector (*P)[])
{
	t_vector pnul, temp, *rotmat;

	ft_write_xyz(&pnul, 0, 0, 0);
	ft_write_xyz(&temp, 0, 0, 1);
	rotmat = rotation_matrix(sq.normal, temp, pnul);

	ft_write_xyz(&pnul, 1, 1, 0);
	(*P)[0] = find_apex_sq(sq, rotmat, pnul);

	ft_write_xyz(&pnul, -1, 1, 0);
	(*P)[1] = find_apex_sq(sq, rotmat, pnul);

	ft_write_xyz(&pnul, 1, -1, 0);
	(*P)[2] = find_apex_sq(sq, rotmat, pnul);

	ft_write_xyz(&pnul, -1, -1, 0);
	(*P)[3] = find_apex_sq(sq, rotmat, pnul);

	free(rotmat);
}
