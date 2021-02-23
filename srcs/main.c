#include "../incs/funct_def.h"

int		exit_program(t_general *gen)
{
	mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
	mlx_destroy_window(gen->mlx.ptr, gen->mlx.win);
	exit(0);
	return (0);
}

void	free_gen(t_general *gen, int fl)
{
	free(gen->scene.rotmat);

	if (fl)
	{
		if (gen->savename != 0)
			free(gen->savename);
		ft_lstclear(&(gen->objs.c), &free);
		ft_lstclear(&(gen->objs.l), &free);
		ft_lstclear(&(gen->objs.sp), &free);
		ft_lstclear(&(gen->objs.pl), &free);
		ft_lstclear(&(gen->objs.sq), &free);
		ft_lstclear(&(gen->objs.tr), &free);
		ft_lstclear(&(gen->objs.cy), &free);
		free(gen->img.img);
		free(gen->img.addr);
		free(gen->mlx.ptr);
		free(gen->mlx.win);
	}
}

void	start_create(t_general *gen, int sav)
{
	gen->mlx.ptr = mlx_init();
	mlx_get_screen_size(gen->mlx.ptr, &(gen->sizex), &(gen->sizey));
	gen->objs.r.x = (gen->objs.r.y > gen->sizex) ? gen->sizex : gen->objs.r.y;
	gen->objs.r.y = (gen->objs.r.y > gen->sizey) ? gen->sizey : gen->objs.r.y;
	gen->mlx.win = mlx_new_window(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y, "miniRT");
	gen->img.img = mlx_new_image(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y);
	gen->img.addr = mlx_get_data_addr(gen->img.img, &(gen->img.bits_per_pixel), &(gen->img.line_length), &(gen->img.endian));
	//printf("\nAA\n\n");

	if (sav)
		save_pic(gen, gen->objs.c->content);
	else
		print_pic(gen, gen->objs.c->content);
}

int		main(int argc, char **argv)
{
	t_general	gen;
	gen.cl = 0;
	gen.num_cam = 0;
	gen.savename = 0;

	clock_t t1 = clock();
	if (argc < 2 || argc > 3)
		return (errors_mes(1, 0));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "-save", 6) != 0)
			return (errors_mes(6, 0));
		else
			if (!(gen.savename = create_bmp_name(argv[1])))
				return (errors_mes(7,0));
	}
	if (parse_file(&(gen.objs), argv[1]))
		return (0);

	start_create(&gen, (argc == 3) ? 1 : 0);
	clock_t t2 = clock();
	printf("\nEnd drawn with time is %f s\n", (double)(t2 - t1) / CLOCKS_PER_SEC);

	/*free_gen(&gen, 0);
	t_vector check = ft_write_xyz(&check, 1, 0, 0);//0.5, 0.5, 1);
	t_vector check0 = ft_write_xyz(&check0, 0, 0, 0);//0.5, 0.5, 1);
	t_vector check2 = ft_write_xyz(&check2, 0, 1, 1);//0.5, 0.5, 1);
	t_vector check3 = ft_write_xyz(&check3, 1, 0, 0);//0.5, 0.5, 1);
	printf("check: %f, %f, %f\n", check3.x, check3.y, check3.z);
	//scene.rotmat = rotation_matrix(cam->nm, objs.orig_cam, cam->cd);
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
	free_gen(&gen, 1);
}
