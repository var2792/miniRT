#ifndef PARSE_PUT_CANVAS_H
# define PARSE_PUT_CANVAS_H

# include "file_help_function.h"
# include "type_def.h"
# include "operat_vecs.h"
# include "parse_put_scene.h"

t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord);
t_scene		parse_put_canvas(t_general gen);
t_vector	trans_pix_v(t_general gen);

#endif
