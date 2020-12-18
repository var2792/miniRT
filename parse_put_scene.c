
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

void			ft_example_scene(t_objscene *scene)
{
	scene->r.x = 512;// 860;// 1920;//
	scene->r.y = 512;// 540;// 1080;//

	scene->a.rat_amlig = 0.1;
	ft_write_xyz(&(scene->a.color), 255, 255, 255);

	ft_write_xyz(&(scene->c[0].coord), 0, 0, 0);
	ft_write_xyz(&(scene->c[0].normal), 0.0, 0.0, 1.0);
	scene->c[0].fov = 80;
	scene->c[0].is = 1;
	scene->c[1].is = 0;

	ft_write_xyz(&(scene->l[0].coord), 0.0, 20.0, 10.0);
	scene->l[0].brirat = 0.9;
	ft_write_xyz(&(scene->l[0].color), 255, 255, 255);
	scene->l[0].is = 1;
	ft_write_xyz(&(scene->l[1].coord), 20.0, 10.0, 10.0);
	scene->l[1].brirat = 0.9;
	ft_write_xyz(&(scene->l[1].color), 255, 255, 255);
	scene->l[1].is = 1;
	scene->l[2].is = 0;
	//printf("it was l, and num = %u\n", scene->l.rgb_16);

	ft_write_xyz(&(scene->sp[0].coord), 0.0, 0.0, 20.0);
	scene->sp[0].diam = 10;
	ft_write_xyz(&(scene->sp[0].color), 10, 0, 255);
	scene->sp[0].is = 1;
	ft_write_xyz(&(scene->sp[1].coord), -5.0, 0.0, 20.0);
	scene->sp[1].diam = 10;
	ft_write_xyz(&(scene->sp[1].color), 255, 0, 0);
	scene->sp[1].is = 1;
	scene->sp[2].is = 0;
	//printf("it was sp, and num = %u\n", scene->sp.rgb_16);

	ft_write_xyz(&(scene->pl[0].coord), 0.0, 0.0, -10.0);
	ft_write_xyz(&(scene->pl[0].normal), 0.0, 1.0, 0.0);
	ft_write_xyz(&(scene->pl[0].color),  0, 0, 225);
	scene->pl[0].is = 1;
	scene->pl[1].is = 0;

	ft_write_xyz(&(scene->sq[0].coord),  0.0, 0.0, 20.6);
	ft_write_xyz(&(scene->sq[0].normal), 1.0, 0.0, 0.0);
	scene->sq[0].size = 12.6;
	ft_write_xyz(&(scene->sq[0].color), 42, 42, 0);
	scene->sq[0].is = 1;
	scene->sq[1].is = 0;

	ft_write_xyz(&(scene->cy[0].coord), 50.0, 0.0, 20.6);
	ft_write_xyz(&(scene->cy[0].normal), 0.0, 0.0, 1.0);
	ft_write_xyz(&(scene->cy[0].color), 10, 0, 255);
	scene->cy[0].diam = 14.2;
	scene->cy[0].heig = 21.42;
	scene->cy[0].is = 1;
	scene->cy[1].is = 0;

	ft_write_xyz(&(scene->tr[0].coord_fir), 10.0, 20.0, 10.0);
	ft_write_xyz(&(scene->tr[0].coord_sec), 10.0, 10.0, 20.0);
	ft_write_xyz(&(scene->tr[0].coord_thi), 20.0, 10.0, 10.0);
	ft_write_xyz(&(scene->tr[0].color), 0, 0, 255);
	scene->tr[0].is = 1;
	scene->tr[1].is = 0;
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
	fd = open("work.rt", O_RDWR);
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
