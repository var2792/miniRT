#ifndef OPERAT_VECS_H
# define OPERAT_VECS_H

# include "file_help_function.h"
# include "type_def.h"

float		scalar_product_vecs(t_vector vec1, t_vector vec2);
t_vector	raz_vecs(t_vector vec1, t_vector vec2);
t_vector	add_t_vecs(float t1, t_vector vec1, float t2, t_vector vec2);
float		lenght_vecs(t_vector vec);

#endif
