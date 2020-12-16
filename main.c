#include "general_minirt.h"

int	mouse_hook(int button, int x, int y, void *param)
{
	if (1L<<3 && param)
	{
		ft_putstr_fd("The window is closed by buttonX.\n", 1);
		exit(0);
	}
	if (1L<<6 && param)
	{
		ft_putnbr_fd(x, 0);
		ft_putchar_fd('\t', 0);
		ft_putnbr_fd(y, 0);
		ft_putchar_fd('\n', 0);
	}
	(void)button;
	return (0);
}

int	press_esc_key(int key, void *param)
{
	if (key == 65307 && param)
	{
		ft_putstr_fd("The window is closed by esc.\n", 1);
		exit(0);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_objscene	objects;
	t_canvas	scene;
	t_vector	pix;

	objects = parse_put_scene(argv);
	scene = parse_put_canvas(objects);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, objects.r.x, objects.r.y, "miniRT");
	pix.x = 0;
	pix.y = 0;
	pix.z = 0;
	float color = 0;
	while (pix.x <= objects.r.x)
	{
		while (pix.y <= objects.r.y)
		{
			color = belong_to_sphere(objects, scene, pix);
			if (color > 0)
				mlx_pixel_put(mlx_ptr, win_ptr, pix.x, pix.y, (int)(color));
			else
				mlx_pixel_put(mlx_ptr, win_ptr, pix.x, pix.y, 0x00222222);
			pix.y++;
		}
		pix.y = 0;
		pix.x++;
	}
	printf("End drawn\n");
	//exit (0);
	mlx_key_hook(win_ptr, press_esc_key, win_ptr);
	mlx_mouse_hook (win_ptr, mouse_hook, win_ptr);
	mlx_loop(mlx_ptr);
	(void)argc;
	(void)argv;
	(void)scene;
}
