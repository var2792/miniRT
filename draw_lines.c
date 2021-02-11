#include "draw_lines.h"

void	next_pof_line(float *px, float *py, float dx, float dy)
{
	*py += (dx == 0) ? 0 : dy / dx;
	*px += 1;
}

void	draw_side_sq(t_general *gen, t_vector P[])
{
	t_vector V[8];
	int i = -1;
	while (++i < 8)
		V[i] = convert_pinv(*gen, P[i]);

	gen->cl = ft_colorvec_unsint(1, gen->objs.sq[0].cl);

	//printf("A\n"); p0.x <= p1.x
	/*while (V[0].x <= V[1].x)
	{
		draw_line_canvas(gen, V[0], V[3]);
		next_pof_line(&(V[0].x), &(V[0].y), V[0].x - V[1].x, V[0].y - V[1].y);
		next_pof_line(&(V[3].x), &(V[3].y), V[3].x - V[2].x, V[3].y - V[2].y);
	}

	while (V[5].x <= V[1].x)
	{
		draw_line_canvas(gen, V[5], V[6]);
		next_pof_line(&(V[5].x), &(V[5].y), V[5].x - V[1].x, V[5].y - V[1].y);
		next_pof_line(&(V[6].x), &(V[6].y), V[6].x - V[2].x, V[6].y - V[2].y);
	}*/
	draw_line_canvas(gen, V[0], V[3]);
	draw_line_canvas(gen, V[1], V[2]);
	draw_line_canvas(gen, V[0], V[1]);
	draw_line_canvas(gen, V[3], V[2]);
	//printf("B\n");

	gen->cl = ft_colorvec_unsint(1, gen->objs.sq[1].cl);
	draw_line_canvas(gen, V[7], V[4]);
	draw_line_canvas(gen, V[4], V[5]);
	draw_line_canvas(gen, V[6], V[5]);
	draw_line_canvas(gen, V[7], V[6]);

	gen->cl = ft_colorvec_unsint(1, gen->objs.sp[0].cl);
	draw_line_canvas(gen, V[3], V[7]);
	draw_line_canvas(gen, V[4], V[0]);
	draw_line_canvas(gen, V[2], V[6]);
	draw_line_canvas(gen, V[5], V[1]);
}

void	draw_line_canvas(t_general *gen, t_vector p0, t_vector p1)
{
	float dx, dy;
	dx = p0.x - p1.x;
	dy = p0.y - p1.y;
	//printf("===> %f %f\n", dx, dy);
	if (fabs(dx) >= fabs(dy))
	{
		//printf("-=--> %f %f %f %f\n", p0.x, p0.y, p1.x, p1.y);
		p0.y = ((dy < 0 && dy / dx < 0) || (dy > 0 && dy / dx > 0)) ? p1.y : p0.y;
		if (p0.x > p1.x)
			while (p1.x <= p0.x)
			{
				//printf("A\n");
				my_mlx_pixel_put(&(gen->img), p1.x, p0.y, (int)(gen->cl));
				next_pof_line(&(p1.x), &(p0.y), dx, dy); //p0.y += dy / dx; //p1.x += 1;
			}
		else
			while (p0.x <= p1.x)
			{
				//printf("B\n");
				my_mlx_pixel_put(&(gen->img), p0.x, p0.y, (int)(gen->cl));
				next_pof_line(&(p0.x), &(p0.y), dx, dy); //p0.y += dy / dx; //p0.x += 1;
			}
	}
	else
	{
		//printf("---> %f %f %f %f\n", p0.x, p0.y, p1.x, p1.y);
		p0.x = ((dx < 0 && dx / dy < 0) || (dx > 0 && dx / dy > 0)) ? p1.x : p0.x;
		if (p0.y > p1.y)
			while (p1.y <= p0.y)
			{
				//printf("C\n");
				my_mlx_pixel_put(&(gen->img), p0.x, p1.y, (int)(gen->cl));
				next_pof_line(&(p1.y), &(p0.x), dy, dx); //p0.x += dx / dy; //p1.y += 1;
			}
		else
			while (p0.y <= p1.y)
			{
				//printf("D\n");
				my_mlx_pixel_put(&(gen->img), p0.x, p0.y, (int)(gen->cl));
				next_pof_line(&(p0.y), &(p0.x), dy, dx); //p0.x += dx / dy; //p0.y += 1;
			}
	}
}
