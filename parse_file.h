#ifndef PARSE_FILE_H
# define PARSE_FILE_H

# include "general_minirt.h"
# include "type_def.h"
# include "points_funs.h"

int		parse_resplution(char **line, t_scobjs *scene);
int		parse_ambient(char **line, t_scobjs *scene);
int		parse_camera(char **line, t_scobjs *scene);
int		parse_light(char **line, t_scobjs *scene);
int		parse_sphere(char **line, t_scobjs *scene);
int		parse_plane(char **line, t_scobjs *scene);
int		parse_square(char **line, t_scobjs *scene);
int		parse_cylinder(char **line, t_scobjs *scene);
int		parse_triangle(char **line, t_scobjs *scene);
int		spase_com_sep(char **line);

int	check_normal(t_vector normal);
int	check_color(t_vector color);

#endif
