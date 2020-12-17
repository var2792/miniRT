#ifndef PARSE_PUT_SCENE_H
# define PARSE_PUT_SCENE_H

# include "gnl/get_next_line.h"
# include "file_help_function.h"
# include "parse_file.h"
# include "type_def.h"

t_objscene		parse_put_scene(char **argv);
void			ft_write_xyz(t_vector *vec, float x, float y, float z);
unsigned int	ft_colorvec_unsint(float br, t_vector vec);
void			ft_write_xyz(t_vector *vec, float x, float y, float z);

#endif
