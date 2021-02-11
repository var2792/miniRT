#ifndef LIGHT_CHANGE_H
# define LIGHT_CHANGE_H

# include "type_def.h"
# include "parse_put_scene.h"
# include "operat_vecs.h"
#include "check_shadows.h"

float	light_change_sp(t_general gen, t_vector p, t_sphere sp, int num_sp);
float	light_change_pl(t_general gen, t_vector p, t_plane pl, int num_pl);
float	light_change_sq(t_general gen, t_vector p, t_square sq, int num_sq);
float	light_change_tr(t_general gen, t_vector p, t_triangle tr, int num_tr);
float	light_change_cy(t_general gen, t_vector p, int num_cy, int fl);

#endif
