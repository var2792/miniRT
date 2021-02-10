#ifndef OPERAT_VECS_H
# define OPERAT_VECS_H

# include "type_def.h"

t_vector	multiply_mat_vec(t_vector *mat, t_vector vec);
float		scalar_product_vecs(t_vector vec1, t_vector vec2);
t_vector	vec_product_vecs(t_vector vec1, t_vector vec2);
t_vector	add_t_vecs(float t1, t_vector vec1, float t2, t_vector vec2);
float		lenght_vecs(t_vector vec);

#endif
