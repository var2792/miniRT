#ifndef BELONG_TO_OBJ_H
# define BELONG_TO_OBJ_H

# include "type_def.h"
# include "light_change.h"
# include "parse_put_canvas.h"
# include "check_see_objs.h"

int		belong_to_sphere(t_general *gen, t_sphere *sp, int *i);
int		belong_to_plane(t_general *gen, t_plane *pl, int *i);
int		belong_to_square(t_general *gen, t_square *sq, int *i);
int		belong_to_triangle(t_general *gen, t_triangle *tr, int *i);
int		belong_to_cylinder(t_general *gen, t_cylinder *cy, int *i);

int		belong_to_cyhead0(t_general gen, t_cylinder cy, t_vector *pcy, int fl);
int		belong_to_cyhead1(t_general gen, t_cylinder cy, t_vector *pcy, int fl);
int		point_in_square(t_square sq, t_vector p);
int		point_in_triangle(t_triangle tr, t_vector p);

#endif
