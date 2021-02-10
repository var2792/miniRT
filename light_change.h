#ifndef LIGHT_CHANGE_H
# define LIGHT_CHANGE_H

# include "type_def.h"
# include "parse_put_scene.h"
# include "operat_vecs.h"
#include "check_shadows.h"

float light_change_sp(t_general gen, t_vector p, int i);
float	light_change_pl(t_general gen, t_vector p, int i);
float	light_change_sq(t_general gen, t_vector p, int i);
float	light_change_tr(t_general gen, t_vector p, int i);
float	light_change_cy(t_general gen, t_vector p, int i, int fl);

#endif
