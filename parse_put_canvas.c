#include "parse_put_canvas.h"

void		ft_null_canvas(t_canvas *canvas, t_objscene objects)
{
	canvas->coord_0.x = (int)(objects.r.x / 2);
	canvas->coord_0.y = (int)(objects.r.y / 2);
	canvas->coord_0.z = 0;
	canvas->viewport.x = 1;
	canvas->viewport.y = 1; //objects.r.y / objects.r.x;
	canvas->viewport.z = 1; //(canvas->viewport.x / tan(objects.c.fov / 2 * 3.1415926 / 180));
	//printf("vx = %f, vy = %f, vz = %f\n", canvas->viewport.x, canvas->viewport.y, canvas->viewport.z);
}

t_canvas	parse_put_canvas(t_objscene objects, t_vector pix)
{
	t_canvas canvas;

	ft_null_canvas(&canvas, objects);
	canvas.coord_v.x = pix.x * canvas.viewport.x / objects.r.x;
	canvas.coord_v.y = pix.y * canvas.viewport.y / objects.r.y;
	canvas.coord_v.z = canvas.viewport.z;
	return (canvas);
}
