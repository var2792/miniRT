#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include "file_help_function.h"
# include "type_def.h"
# include "points_funs.h"

int		parse_resplution(char **line, t_objscene *scene);
int		parse_ambient(char **line, t_objscene *scene);
int		parse_camera(char **line, t_objscene *scene);
int		parse_light(char **line, t_objscene *scene);
int		parse_sphere(char **line, t_objscene *scene);
int		parse_plane(char **line, t_objscene *scene);
int		parse_square(char **line, t_objscene *scene);
int		parse_cylinder(char **line, t_objscene *scene);
int		parse_triangle(char **line, t_objscene *scene);
void	spase_com_sep(char **line);

#endif
