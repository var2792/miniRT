#ifndef BELONG_TO_OBJ_H
# define BELONG_TO_OBJ_H

# include "file_help_function.h"
# include "type_def.h"
# include "light_change.h"
# include "parse_put_canvas.h"
# include "check_see_objs.h"

float		belong_to_sphere(t_general *gen, int *i);
int			belong_to_plane(t_general *gen, int *i);
int			belong_to_square(t_objscene objects, t_canvas scene, t_vector pix);
int			belong_to_cylinder(t_objscene objects, t_canvas scene, t_vector pix);
int			belong_to_triangle(t_objscene objects, t_canvas	scene, t_vector pix);

#endif
