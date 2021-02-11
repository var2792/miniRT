
#include "parse_put_scene.h"

void			ft_write_xyz(t_vector *vec, float x, float y, float z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

unsigned int	ft_colorvec_unsint(float br, t_vector vec)
{
	unsigned int num;
	unsigned int r[2];
	unsigned int g[2];
	unsigned int b[2];

	r[0] = (unsigned int)(vec.x) / 16;
	r[1] = (unsigned int)(vec.x) % 16;
	g[0] = (unsigned int)(vec.y) / 16;
	g[1] = (unsigned int)(vec.y) % 16;
	b[0] = (unsigned int)(vec.z) / 16;
	b[1] = (unsigned int)(vec.z) % 16;
	/*printf("r[0] = %u, r[1] = %u\n", r[0], r[1]);
	printf("g[0] = %u, g[1] = %u\n", g[0], g[1]);
	printf("b[0] = %u, b[1] = %u\n", b[0], b[1]);*/
	num = (r[0] * 16 + r[1]) * 16 * 16 * 16 * 16 + (g[0] * 16 + g[1]) * 16 * 16 + b[0] * 16 + b[1];
	return (br * num);
}

int		ft_check_input_chars(char **line, t_scobjs *scene)
{
	if ((*line)[0] == 'R')
		return (parse_resplution(line, scene));

	if ((*line)[0] == 'A')
		return (parse_ambient(line, scene));

	if ((*line)[0] == 'c' && (*line)[1] != 'y')
		return (parse_camera(line, scene));

	if ((*line)[0] == 'l')
		return (parse_light(line, scene));

	if ((*line)[0] == 's' && (*line)[1] == 'p')
		return (parse_sphere(line, scene));

	if ((*line)[0] == 'p' && (*line)[1] == 'l')
		return (parse_plane(line, scene));

	if ((*line)[0] == 's' && (*line)[1] == 'q')
		return (parse_square(line, scene));

	if ((*line)[0] == 'c' && (*line)[1] == 'y')
		return (parse_cylinder(line, scene));

	if ((*line)[0] == 't' && (*line)[1] == 'r')
		return (parse_triangle(line, scene));

	return (1);
}

void			ft_null_scene(t_scobjs *scene)
{

	scene->r.is = 0;

	scene->a.is = 0;
	ft_write_xyz(&(scene->orig_cam), 0, 0, 1);

	scene->c = NULL;
	scene->l = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->sq = NULL;
	scene->tr = NULL;
	scene->cy = NULL;
}

int check_name_file(char *argv)
{
	int i;

	i = 0;
	while (argv[i] && argv[i] != '.')
		i++;
    if (!argv[i] || i < 1)
		return (1);
	else if (argv[i + 1] && argv[i + 1] != 'r')
		return (1);
	else if (argv[i + 2] && argv[i + 2] != 't')
		return (1);
	else if (argv[i + 3] != '\0')
		return (1);
	return (0);
}

int		parse_file(t_scobjs *objs, char *argv)
{
	int n;
	int fd;
	int len;
	char *line;
	char *save_line;

	n = 1;
	if (check_name_file(argv))
		return (1);
	if ((fd = open(argv, O_RDWR)) < 0)
		return (1);
	ft_null_scene(objs);
	while (n > 0)
	{
		n = get_next_line(fd, &line);
		save_line = line;
		len = ft_strilen(line);
		if (*line && len > 1)
		{
			while (ft_check_isspace(*line))
				line++;
			len = ft_check_input_chars(&line, objs);
			//while (ft_check_isspace(*line))
				//line++;
			if (len)
			{
				ft_putstr_fd("Error: Not correct input file.\n", 1);
				ft_putstr_fd(save_line, 1);
				ft_putstr_fd(" <<=-\n", 1);
				free(save_line);
				return (1);
			}
		}
		free(save_line);
	}
	if (!objs->r.is || !objs->c || !objs->a.is)
		return (1);
	return (0);
	(void)argv;
}
