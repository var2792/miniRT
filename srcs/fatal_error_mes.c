#include "../incs/funct_def.h"

int errors_mes(int n, char **help)
{
	if (n == 1)
		ft_putstr_fd("Error: Wrong function call.\n", 1);
	if (n == 2)
	{
		ft_putstr_fd("Error: Wrong line\t--\t", 1);
		ft_putstr_fd(*help, 1);
		ft_putstr_fd("\n", 1);
		free(*help);
	}
	if (n == 3)
		ft_putstr_fd("Error: Not full file.\n", 1);
	if (n == 4)
		ft_putstr_fd("Error: Wrong file name.\n", 1);
	if (n == 5)
		ft_putstr_fd("Error: No file.\n", 1);
	return (1);
	(void)help;
}

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