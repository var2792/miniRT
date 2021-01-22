#ifndef CHECK_SHADOWS_H
# define CHECK_SHADOWS_H

# include "file_help_function.h"
# include "type_def.h"
# include "parse_put_scene.h"
# include "operat_vecs.h"

float		check_shadow(int num_l, int num_sp, t_objscene objects, t_vector p);
float		check_shadow_sp(int num_l, int num_sp, t_objscene objects, t_vector p);

#endif
