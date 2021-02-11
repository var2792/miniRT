#ifndef OPERAT_VECS_H
# define OPERAT_VECS_H

# include "type_def.h"

t_vector	mult_m_v(t_vector *mat, t_vector vec);
float		dot_prv(t_vector vec1, t_vector vec2);
t_vector	cross_prv(t_vector vec1, t_vector vec2);
t_vector	sum_vs(float t1, t_vector vec1, float t2, t_vector vec2);
float		len_vec(t_vector vec);

#endif
