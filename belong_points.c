#include "belong_to_obj.h"

int			point_in_square(t_square sq, t_vector p)
{
	float x, y;

	x = dot_prv(sum_vs(1, p, -1, sq.ps[0]), sum_vs(1, sq.ps[1], -1, sq.ps[0])) / dot_prv(sum_vs(1, sq.ps[1], -1, sq.ps[0]), sum_vs(1, sq.ps[1], -1, sq.ps[0]));
	y = dot_prv(sum_vs(1, p, -1, sq.ps[0]), sum_vs(1, sq.ps[2], -1, sq.ps[0])) / dot_prv(sum_vs(1, sq.ps[2], -1, sq.ps[0]), sum_vs(1, sq.ps[2], -1, sq.ps[0]));

	if (x >= 0 && x <= 1 && y >= 0 && y <= 1)
		return (1);
	return (0);
}

int			point_in_triangle(t_triangle tr, t_vector p)
{
	float x, y;

	x = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd2, -1, tr.cd1)) * dot_prv(sum_vs(1, tr.cd3, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)));
	y = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1), sum_vs(1, tr.cd2, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd2, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1))) / x;
	x = (dot_prv(sum_vs(1, tr.cd2, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) - dot_prv(sum_vs(1, tr.cd3, -1, tr.cd1), sum_vs(1, tr.cd3, -1, tr.cd1)) * dot_prv(sum_vs(1, p, -1, tr.cd1), sum_vs(1, tr.cd2, -1, tr.cd1))) / x;
	if (x >= 0 && y >= 0 && x + y <= 1)
		return (1);
	return (0);
	(void)tr;
	(void)p;
}
