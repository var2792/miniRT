#include "../incs/funct_def.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		exit_program(t_general *gen)
{
	mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
	mlx_destroy_window(gen->mlx.ptr, gen->mlx.win);
	free_gen(gen, 1);
	exit(0);
	return (0);
}

void	free_gen(t_general *gen, int fl)
{
	free(gen->scene.rotmat);

	if (fl)
	{
		ft_lstclear(&(gen->objs.c), &free);
		ft_lstclear(&(gen->objs.l), &free);
		ft_lstclear(&(gen->objs.sp), &free);
		ft_lstclear(&(gen->objs.pl), &free);
		ft_lstclear(&(gen->objs.sq), &free);
		ft_lstclear(&(gen->objs.tr), &free);
		ft_lstclear(&(gen->objs.cy), &free);
		//free(gen->img.img);
		//free(gen->img.addr);
		//free(gen->mlx.ptr);
		//free(gen->mlx.win);
	}
}

int		main(int argc, char **argv)
{
	t_general	gen;
	gen.cl = 0;
	gen.num_cam = 0;

	clock_t t1 = clock();
	if (argc < 2 || argc > 3)
		return (errors_mes(1, 0));
	if (parse_file(&(gen.objs), argv[1]))
		return (0);

	start_create(&gen);
	clock_t t2 = clock();
	printf("\nEnd drawn with time is %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

	/*t_vector check = ft_write_xyz(&check, 1, 1, 1);//0.5, 0.5, 1);
	t_vector check0 = ft_write_xyz(&check0, 0, 0, 0);//0.5, 0.5, 1);
	t_vector check2 = ft_write_xyz(&check2, 0, 1, 1);//0.5, 0.5, 1);
	t_vector check3 = ft_write_xyz(&check3, 1, 1, 1);//0.5, 0.5, 1);
	printf("check: %f, %f, %f\n", check3.x, check3.y, check3.z);
	gen.scene.rotmat = rotation_matrix(check2, check, check0);
	check3 = mult_m_v(gen.scene.rotmat, check3);
	printf("check: %f, %f, %f\n", check3.x, check3.y, check3.z);
	gen.scene.rotmat = rotation_matrix(check, check2, check0);
	check3 = mult_m_v(gen.scene.rotmat, check3);
	printf("check: %f, %f, %f\n", check3.x, check3.y, check3.z);*/
	mlx_hook(gen.mlx.win, 2, 1L << 0, press_keys, &gen);
	mlx_hook(gen.mlx.win, 17, 1L << 17, exit_program, &gen);
	//mlx_mouse_hook (gen.mlx.win, mouse_hook, 0);
	mlx_loop(gen.mlx.ptr);
}
