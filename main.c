#include "general_minirt.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		exit_program(t_my_mlx *my_mlx)
{
	//printf("Hiiiii\n");
	mlx_clear_window(my_mlx->ptr, my_mlx->win);
	mlx_destroy_window(my_mlx->ptr, my_mlx->win);
	exit(0);
	return (0);
}

int	mouse_hook(int button, int x, int y)
{
	if (1L<<6)
	{
		ft_putnbr_fd(x, 1);
		ft_putchar_fd('\t', 1);
		ft_putnbr_fd(y, 0);
		ft_putchar_fd('\n', 1);
	}
	(void)button;
	return (0);
}

void	free_gen(t_general *gen)
{
	free(gen->scene.rotmat);
	//free(gen->img.img);
	//free(gen->img.addr);
}

void	print_pic(t_general *gen, t_camera *cam, int *i)
{
	//gen->img.img = mlx_new_image(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y);
	//gen->img.addr = mlx_get_data_addr(gen->img.img, &(gen->img.bits_per_pixel), &(gen->img.line_length), &(gen->img.endian));
	gen->scene = parse_put_canvas(gen->objs, cam);
	ft_write_xyz(&(gen->pix), 0, 0, 0);
	while (gen->pix.x < gen->objs.r.x)
	{
		while (gen->pix.y < gen->objs.r.y)
		{
			gen->scene.cdv = trans_pixv(*gen);
			gen->cl = -5;
			//printf("\nAA\n\n");
			if (gen->objs.sp != NULL)
				belong_to_sphere(gen, gen->objs.sp->content, i);
			gen->pix.z = 0;
			if (gen->objs.pl != NULL)
				belong_to_plane(gen, gen->objs.pl->content, i);
			gen->pix.z = 0;
			if (gen->objs.sq != NULL)
				belong_to_square(gen, gen->objs.sq->content, i);
			gen->pix.z = 0;
			if (gen->objs.tr != NULL)
				belong_to_triangle(gen, gen->objs.tr->content, i);
			gen->pix.z = 0;
			//t_cylinder *cy = gen->objs.cy->content;
			//printf("Cy %f %f %f\n", cy->cl.x, cy->cl.y, cy->cl.z);
			if (gen->objs.cy != NULL)
				belong_to_cylinder(gen, gen->objs.cy->content, i);
			if (gen->cl >= 0)
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, (int)(gen->cl));
			else
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, 0);
				//else //if (gen->pix.z == 0)
					//my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, 0x00171717);
			gen->pix.z = 0;
			gen->pix.y += 1;
		}
		gen->pix.y = 0;
		gen->pix.x += 1;
	}

	gen->pix.z = 0;

	mlx_put_image_to_window(gen->mlx.ptr, gen->mlx.win, gen->img.img, 0, 0);
	printf("\nc.x = %f, c.y = %f, c.z = %f,\n", cam->cd.x, cam->cd.y, cam->cd.z);
	//printf("c.n.x = %f, c.n.y = %f, c.n.z = %f,\n", gen->objs.c[gen->num_cam].nm.x, gen->objs.c[gen->num_cam].nm.y, gen->objs.c[gen->num_cam].nm.z);
	(void)cam;
}

int	press_keys(int key, t_general *gen)
{
	t_list *next;
	t_camera *cam;
	int i = 0;
	if (key == 65307)
	{
		ft_putstr_fd("\nThe window is closed by esc.\n", 1);
		return (exit_program(&(gen->mlx)));
	}

	if (key == 65363) //->
	{
		if ((next = ft_lstnum(gen->objs.c, gen->num_cam + 1)) != NULL)
		{
			ft_putstr_fd(" C->\n", 1);
			gen->num_cam += 1;
			mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
			free_gen(gen);
			print_pic(gen, next->content, &i);
		}
		else
		{
			ft_putstr_fd(" C->\n", 1);
			mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
			free_gen(gen);
			gen->num_cam = 0;
			next = ft_lstnum(gen->objs.c, gen->num_cam);
			print_pic(gen, next->content, &i);
		}
	}

	if (key == 65361) //<-
	{

		if ((next = ft_lstnum(gen->objs.c, gen->num_cam - 1)) != NULL)
		{
			ft_putstr_fd(" C<-\n", 1);
			gen->num_cam -= 1;
			mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
			free_gen(gen);
			print_pic(gen, next->content, &i);
		}
		else
		{
			ft_putstr_fd(" C<-\n", 1);
			mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
			free_gen(gen);
			gen->num_cam = ft_lstsize(gen->objs.c) - 1;
			next = ft_lstnum(gen->objs.c, gen->num_cam);
			print_pic(gen, next->content, &i);
		}
	}

	if (key == 119) //w
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.z += 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	if (key == 115) //s
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.z -= 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	if (key == 97) //a
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.x -= 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	if (key == 100) //d
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.x += 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	if (key == 122) //z
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.y += 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	if (key == 120) //x
	{
		cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
		cam->cd.y -= 2;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		print_pic(gen, cam, &i);
	}
	//ft_putnbr_fd(key, 1); ft_putstr_fd("\n", 1);
	return (0);
	(void)i;
}
 //sq 0.0,5.0,16.0 0,1,0 6.0 200,200,50 //pl -21.0,0.0,20.0 1.0,0.0,0.0 0,0,225
int		main(int argc, char **argv)
{
	t_general	gen;
	int i = 0;
	gen.cl = 0;
	gen.num_cam = 0;

	clock_t t1 = clock();
	if (argc < 2 || argc > 3)
	{
		ft_putstr_fd("Error: Wrong function call.\n", 1);
		return (0);
	}
	if (parse_file(&(gen.objs), argv[1]))
		return (0);
	gen.mlx.ptr = mlx_init();
	gen.mlx.win = mlx_new_window(gen.mlx.ptr, gen.objs.r.x, gen.objs.r.y, "miniRT");
	gen.img.img = mlx_new_image(gen.mlx.ptr, gen.objs.r.x, gen.objs.r.y);
	gen.img.addr = mlx_get_data_addr(gen.img.img, &(gen.img.bits_per_pixel), &(gen.img.line_length), &(gen.img.endian));
	//printf("\nAA\n\n");

	print_pic(&gen, gen.objs.c->content, &i);

	clock_t t2 = clock();
	printf("\nEnd drawn with time is %f s and %i iterations\n", (double)(t2 - t1) / CLOCKS_PER_SEC, i);

	/*t_vector check;
	ft_write_xyz(&check, -1, 0, 0);//0.5, 0.5, 1);
	check = mult_m_v(gen.scene.rotmat, check);
	printf("check: %f, %f, %f\n", check.x, check.y, check.z);*/
	mlx_hook(gen.mlx.win, 2, 1L << 0, press_keys, &gen);
	mlx_hook(gen.mlx.win, 17, 1L << 17, exit_program, 0);
	mlx_mouse_hook (gen.mlx.win, mouse_hook, 0);
	mlx_loop(gen.mlx.ptr);
	(void)argc;
	(void)argv;
	(void)gen.scene;
}
