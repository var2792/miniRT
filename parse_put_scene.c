
#include "parse_put_scene.h"

int		ft_isspase(int c)
{
	if (c == 32 && c == '\t')
		return (1);
	else
		return (0);
}

int		ft_check_input_chars(char *line)
{
	if (ft_findchr("RAl", line[0]) >= 0)
		return (0);
	if (ft_findchr("p", line[0]) >= 0 && line[1] && ft_findchr("l", line[1]) >= 0)
		return (0);
	if (ft_findchr("s", line[0]) >= 0 && line[1] && (ft_findchr("p", line[1]) >= 0 || ft_findchr("q", line[1]) >= 0))
		return (0);
	if (ft_findchr("c", line[0]) >= 0 && line[1] && (ft_findchr("y", line[1]) >= 0 || ft_findchr(" \t", line[1]) >= 0))
		return (0);
	if (ft_findchr("t", line[0]) >= 0 && line[1] && ft_findchr("r", line[1]) >= 0)
		return (0);
	return (1);
}

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

void			ft_null_scene(t_objscene *scene)
{
	scene->r.x = 512;// 860;// 1920;//
	scene->r.y = 512;// 540;// 1080;//

	scene->a.rat_amlig = 0.1;
	ft_write_xyz(&(scene->a.color), 255, 255, 255);
	scene->a.rgb_16 = ft_colorvec_unsint(1, scene->a.color);
	//printf("it was a, and num = %u\n", scene->a.rgb_16);

	ft_write_xyz(&(scene->c.coord), 0, 0, 0);
	ft_write_xyz(&(scene->c.normal), 0.0, 0.0, 1.0);
	scene->c.fov = 80;

	ft_write_xyz(&(scene->l.coord), 0.0, 20.0, 10.0);
	scene->l.brirat = 0.9;
	ft_write_xyz(&(scene->l.color), 255, 255, 255);
	scene->l.rgb_16 = ft_colorvec_unsint(1, scene->l.color);
	//printf("it was l, and num = %u\n", scene->l.rgb_16);

	ft_write_xyz(&(scene->sp.coord), 0.0, 0.0, 20.0);
	scene->sp.diam = 10;
	ft_write_xyz(&(scene->sp.color), 10, 0, 255);
	scene->sp.rgb_16 = ft_colorvec_unsint(1, scene->sp.color);
	//printf("it was sp, and num = %u\n", scene->sp.rgb_16);

	ft_write_xyz(&(scene->pl.coord), 0.0, 0.0, -10.0);
	ft_write_xyz(&(scene->pl.normal), 0.0, 1.0, 0.0);
	ft_write_xyz(&(scene->pl.color),  0, 0, 225);
	scene->pl.rgb_16 = ft_colorvec_unsint(1, scene->pl.color);
	//printf("it was pl, and num = %u\n", scene->pl.rgb_16);

	ft_write_xyz(&(scene->sq.coord),  0.0, 0.0, 20.6);
	ft_write_xyz(&(scene->sq.normal), 1.0, 0.0, 0.0);
	scene->sq.size = 12.6;
	ft_write_xyz(&(scene->sq.color), 255, 0, 255);
	scene->sq.rgb_16 = ft_colorvec_unsint(1, scene->sq.color);
	//printf("it was sq, and num = %u\n", scene->sq.rgb_16);

	ft_write_xyz(&(scene->cy.coord), 50.0, 0.0, 20.6);
	ft_write_xyz(&(scene->cy.normal), 0.0, 0.0, 1.0);
	ft_write_xyz(&(scene->cy.color), 10, 0, 255);
	scene->cy.diam = 14.2;
	scene->cy.heig = 21.42;
	scene->cy.rgb_16 = ft_colorvec_unsint(1, scene->cy.color);
	//printf("it was cy, and num = %u\n", scene->cy.rgb_16);

	ft_write_xyz(&(scene->tr.coord_fir), 10.0, 20.0, 10.0);
	ft_write_xyz(&(scene->tr.coord_sec), 10.0, 10.0, 20.0);
	ft_write_xyz(&(scene->tr.coord_thi), 20.0, 10.0, 10.0);
	ft_write_xyz(&(scene->tr.color), 0, 0, 255);
	scene->tr.rgb_16 = ft_colorvec_unsint(1, scene->tr.color);
	//printf("it was tr, and num = %u\n", scene->tr.rgb_16);
}

t_objscene		parse_put_scene(char **argv)
{
	//int n;
	//int len;
	(void)argv;
	//char *line;
	t_objscene all_scene;

	//n = 1;
	//len = 5;
	ft_null_scene(&all_scene);
	/*while (n > 0 && len > 0)
	{
		n = get_next_line(0, &line);
		len = ft_strlen(line);
		while (*line)
		{
			while (ft_isspase(*line))
				line++;
			if (ft_check_input_chars(line))
			{
				ft_putstr_fd("Not correct input.\n", 1);
				return ;
			}
			else
				break;
		}
		free(line);
	}*/
	return (all_scene);
}
