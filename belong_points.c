#include "belong_to_obj.h"

int			point_in_square(t_square sq, t_vector p)
{
	float x, y;

	x = scalar_product_vecs(add_t_vecs(1, p, -1, sq.ps[0]), add_t_vecs(1, sq.ps[1], -1, sq.ps[0])) / scalar_product_vecs(add_t_vecs(1, sq.ps[1], -1, sq.ps[0]), add_t_vecs(1, sq.ps[1], -1, sq.ps[0]));
	y = scalar_product_vecs(add_t_vecs(1, p, -1, sq.ps[0]), add_t_vecs(1, sq.ps[2], -1, sq.ps[0])) / scalar_product_vecs(add_t_vecs(1, sq.ps[2], -1, sq.ps[0]), add_t_vecs(1, sq.ps[2], -1, sq.ps[0]));

	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}

int			point_in_triangle(t_triangle tr, t_vector p)
{
	float x, y;

	x = (scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) - scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)));
	y = (scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, p, -1, tr.coord_fir), add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir)) - scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, p, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir))) / x;
	x = (scalar_product_vecs(add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, p, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) - scalar_product_vecs(add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir), add_t_vecs(1, tr.coord_thi, -1, tr.coord_fir)) * scalar_product_vecs(add_t_vecs(1, p, -1, tr.coord_fir), add_t_vecs(1, tr.coord_sec, -1, tr.coord_fir))) /  x;
	if (x >= 0 && y >= 0 && x + y <= 1)
		return (1);
	return (0);
	(void)tr;
	(void)p;
}
