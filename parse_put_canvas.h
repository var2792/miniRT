#ifndef PARSE_PUT_CANVAS_H
# define PARSE_PUT_CANVAS_H

# include "type_def.h"
# include "operat_vecs.h"
# include "parse_put_scene.h"

t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord);
t_scene		parse_put_canvas(t_scobjs objs, t_camera *c);//(t_general gen);//
t_vector	trans_pixv(t_general gen);

#endif
