#ifndef CHECK_SHADOWS_H
# define CHECK_SHADOWS_H

# include "type_def.h"
# include "parse_put_scene.h"
# include "operat_vecs.h"
# include "belong_to_obj.h"

float		check_shadow(t_light num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_sp(t_light num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_pl(t_light num_l, int num_pl, t_scobjs objects, t_vector p);
float		check_shadow_sq(t_light num_l, int num_sq, t_scobjs objects, t_vector p);
float		check_shadow_tr(t_light num_l, int num_tr, t_scobjs objects, t_vector p);
float		check_shadow_cy(t_light num_l, int num_cy, t_scobjs objects, t_vector p);
float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p);

#endif
