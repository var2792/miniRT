#ifndef CHECK_SHADOWS_H
# define CHECK_SHADOWS_H

# include "type_def.h"
# include "parse_put_scene.h"
# include "operat_vecs.h"
# include "belong_to_obj.h"

float		check_shadow(int num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_sp(int num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_pl(int num_l, int num_pl, t_scobjs objects, t_vector p);
float		check_shadow_sq(int num_l, int num_sq, t_scobjs objects, t_vector p);
float		check_shadow_tr(int num_l, int num_tr, t_scobjs objects, t_vector p);
float		check_shadow_cy(int num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p);

#endif
