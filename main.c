#include "general_minirt.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int		exit_program(t_my_mlx *my_mlx)
{
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

int	press_esc_key(int key, t_my_mlx *my_mlx)
{
	if ((key == 65307 || key == 11965507))
	{
		ft_putstr_fd("The window is closed by esc.\n", 1);
		return (exit_program(my_mlx));
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_general	gen;
	int n = 1;
	int i = 0;
	gen.color = 0;
	gen.num_cam = 0;

	gen.objects = parse_put_scene(argv);
	gen.scene = parse_put_canvas(gen);
	gen.mlx.ptr = mlx_init();
	gen.mlx.win = mlx_new_window(gen.mlx.ptr, gen.objects.r.x, gen.objects.r.y, "miniRT");
    gen.img.img = mlx_new_image(gen.mlx.ptr, gen.objects.r.x, gen.objects.r.y);
	gen.img.addr = mlx_get_data_addr(gen.img.img, &(gen.img.bits_per_pixel), &(gen.img.line_length), &(gen.img.endian));
	//printf("AA\n");
	ft_write_xyz(&(gen.pix), 0, 0, 0);
	clock_t t1 = clock();
	while (gen.pix.x <= gen.objects.r.x)
	{
		while (gen.pix.y <= gen.objects.r.y)
		{
			gen.color = -5;
			belong_to_sphere(&gen, &i);
			gen.pix.z = 0;
			belong_to_plane(&gen, &i);
				if (gen.color >= 0)
					my_mlx_pixel_put(&(gen.img), gen.pix.x, gen.pix.y, (int)(gen.color));
				//else //if (gen.pix.z == 0)
					//my_mlx_pixel_put(&(gen.img), gen.pix.x, gen.pix.y, 0x00171717);
			gen.pix.z = 0;
			//if (pix.x == 285 && pix.y == 254)
				//printf("%d\n", (int)color);
			gen.pix.y += n;
		}
		gen.pix.y = 0;
		gen.pix.x += n;
	}
    mlx_put_image_to_window(gen.mlx.ptr, gen.mlx.win, gen.img.img, 0, 0);
	clock_t t2 = clock();
	printf("O.c.x = %f, O.c.y = %f, O.c.z = %f,\n", gen.objects.c[0].coord.x, gen.objects.c[0].coord.y, gen.objects.c[0].coord.z);
	printf("c.n.x = %f, c.n.y = %f, c.n.z = %f,\n", gen.objects.c[0].normal.x, gen.objects.c[0].normal.y, gen.objects.c[0].normal.z);
	printf("End drawn with time is %f s and %i iterations\n", (double)(t2 - t1) / CLOCKS_PER_SEC, i);
	
	t_vector check;
	ft_write_xyz(&check, 0, 0, 1);//0.5, 0.5, 1);
	check = multiply_mat_vec(gen.scene.rotmat, check);
	printf("check: %f, %f, %f\n", check.x, check.y, check.z);
	mlx_hook(gen.mlx.win, 2, 1L << 0, press_esc_key, &(gen.mlx));
	mlx_hook(gen.mlx.win, 17, 1L << 17, exit_program, &(gen.mlx));
	mlx_mouse_hook (gen.mlx.win, mouse_hook, 0);
	mlx_loop(gen.mlx.ptr);
	(void)argc;
	(void)argv;
	(void)gen.scene;
}
