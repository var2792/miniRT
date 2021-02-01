#ifndef DRAWING_OBJS_H
# define DRAWING_OBJS_H

# include "file_help_function.h"
# include "type_def.h"
# include "light_change.h"
# include "parse_put_canvas.h"
# include "check_see_objs.h"
# include "square_fun.h"
# include "draw_lines.h"

int			belong_to_square(t_general *gen, int *i);
int			belong_to_cylinder(t_objscene objects, t_scene scene, t_vector pix);
int			belong_to_triangle(t_objscene objects, t_scene	scene, t_vector pix);

#endif
