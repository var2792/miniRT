# include "parse_file.h"

int	check_normal(t_vector normal)
{
	if (normal.x < -1 || normal.x > 1)
		return (1);
	if (normal.y < -1 || normal.y > 1)
		return (1);
	if (normal.x < -1 || normal.z > 1)
		return (1);
	if (len_vec(normal) < 0.01)
		return (1);
	return (0);
}

int	check_color(t_vector color)
{
	if (color.x < 0 || color.x > 255)
		return (1);
	if (color.y < 0 || color.y > 255)
		return (1);
	if (color.z < 0 || color.z > 255)
		return (1);
	return (0);
}
