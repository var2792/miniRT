#ifndef DRAW_LINES_H
# define DRAW_LINES_H

# include "file_help_function.h"
# include "type_def.h"
# include "general_minirt.h"
# include "light_change.h"
# include "parse_put_canvas.h"
# include "check_see_objs.h"

void	draw_side_sq(t_general *gen, t_vector P[]);
void	draw_line_canvas(t_general *gen, t_vector p0, t_vector p1);

#endif
