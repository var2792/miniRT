#include "parse_put_canvas.h"

t_canvas	parse_put_canvas(t_objscene objects)
{
	t_canvas canvas;

	canvas.coord_0.x = (int)(objects.c[0].coord.x);
	canvas.coord_0.y = (int)(objects.c[0].coord.y);
	canvas.coord_0.z = (int)(objects.c[0].coord.z);
	canvas.viewport.x = 1;
	canvas.viewport.y = objects.r.y / objects.r.x;
	canvas.viewport.z = (canvas.viewport.x / tan(objects.c[0].fov / 2 * 3.1415926 / 180));
	//printf("vx = %f, vy = %f, vz = %f\n", canvas->viewport.x, canvas->viewport.y, canvas->viewport.z);
	return (canvas);
}
