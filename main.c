#include "general_minirt.h"

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
	scene = parse_put_canvas(objects, pix);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, objects.r.x, objects.r.y, "miniRT");
	int x = 200, y = 200, color = 0x0000AA00;
	while (x < 300)
	{
		while (y < 300)
		{
			mlx_pixel_put(mlx_ptr, win_ptr, x, y, color);
			y++;
		}
		y = 200;
		x++;
	}

	mlx_key_hook(win_ptr, press_esc_key, win_ptr);
	mlx_loop(mlx_ptr);
	(void)argc;
	(void)argv;
	(void)scene;
}
