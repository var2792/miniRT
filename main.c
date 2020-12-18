#include "general_minirt.h"

int	my_close(int keycode, void	*mlx_ptr, void	*win_ptr)
{
	(void)keycode;
    mlx_destroy_window(mlx_ptr, win_ptr);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	if (1L<<6 && param)
	{
		ft_putnbr_fd(x, 1);
		ft_putchar_fd('\t', 1);
		ft_putnbr_fd(y, 0);
		ft_putchar_fd('\n', 1);
	}
	(void)button;
	return (0);
}

int	press_esc_key(int key, void *param)
{
	if ((key == 65307 || key == 11965507) && param)
	{
		ft_putstr_fd("The window is closed by esc.\n", 1);
		exit(0);

	}
	return (0);
}

void	put_npixel(void *mlx_ptr, void *win_ptr, t_vector pix, int color, int n)
{
	int i;
	int j;

	i = 0;
	while (i <= n)
	{
		j = 0;
		while (j <= n)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, pix.x + i, pix.y + j, color);
			j++;
		}
		i++;
	}
}

int		main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_objscene	objects;
	t_canvas	scene;
	t_vector	pix;
	float color = 0;
	int n = 4;

	objects = parse_put_scene(argv);
	scene = parse_put_canvas(objects);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, objects.r.x, objects.r.y, "miniRT");
	ft_write_xyz(&pix, 0, 0, 0);
	while (pix.x <= objects.r.x)
	{
		while (pix.y <= objects.r.y)
		{
			while (objects.sp[(int)pix.z].is)
			{
				color = belong_to_sphere(objects, scene, pix);
				if (color >= 0)
					put_npixel(mlx_ptr, win_ptr, pix, (int)(color), n);
				else if (pix.z == 0)
					put_npixel(mlx_ptr, win_ptr, pix, 0x00222222, n);
				pix.z += 1;
			}
			pix.z = 0;
			//if (pix.x == 285 && pix.y == 254)
				//printf("%d\n", (int)color);
			pix.y += n;
		}
		pix.y = 0;
		pix.x += n;
	}
	printf("c.n.x = %f, c.n.y = %f, c.n.z = %f,\n", objects.c[0].normal.x, objects.c[0].normal.y, objects.c[0].normal.z);
	printf("End drawn\n");
	mlx_key_hook(win_ptr, press_esc_key, win_ptr);
		//mlx_destroy_window(mlx_ptr, win_ptr);
	//mlx_hook(win_ptr, 4, 1L<<0, my_close, win_ptr);
	mlx_mouse_hook (win_ptr, mouse_hook, win_ptr);
	mlx_loop(mlx_ptr);
	(void)argc;
	(void)argv;
	(void)scene;
}
