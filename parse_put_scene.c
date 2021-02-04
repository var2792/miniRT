
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

int		ft_check_input_chars(char **line, t_objscene *scene)
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

void			ft_null_scene(t_objscene *scene)
{
	int i;

	scene->r.is = 0;

	scene->a.rat_amlig = 0;
	ft_write_xyz(&(scene->a.color), 0, 0, 0);
	ft_write_xyz(&(scene->orig_cam), 0, 0, 1);

	i = -1;
	while (++i < 50)
	{
		scene->c[i].is = 0;
		scene->l[i].is = 0;
		scene->sp[i].is = 0;
		scene->pl[i].is = 0;
		scene->sq[i].is = 0;
		scene->cy[i].is = 0;
		scene->tr[i].is = 0;
	}
}

t_objscene		parse_put_scene(char **argv)
{
	t_objscene all_scene;
	//ft_example_scene(&all_scene);
	int n;
	int fd;
	int len;
	char *line;
	char *save_line;

	n = 1;
	//fd = open("tests/work.rt", O_RDWR);
	fd = open("tests/temp.rt", O_RDWR);
	ft_null_scene(&all_scene);
	while (n > 0)
	{
		n = get_next_line(fd, &line);
		save_line = line;
		len = ft_strlen(line);
		if (*line && len > 1)
		{
			while (ft_check_isspace(*line))
				line++;
			if (ft_check_input_chars(&line, &all_scene))
			{
				ft_putstr_fd("Not correct input.\n", 1);
				break ;
			}
		}
		free(save_line);
	}
	return (all_scene);
	(void)argv;
}
