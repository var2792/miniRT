/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	if (fl > 0)
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
		free(gen->mlx.ptr);
	}
	if (fl == 2)
	{
		free(gen->img.addr);
		free(gen->mlx.win);
	}
}

void	start_create(t_general *gen, int sav)
{
	gen->mlx.ptr = mlx_init();
	mlx_get_screen_size(gen->mlx.ptr, &(gen->sizex), &(gen->sizey));
	gen->objs.r.x = (gen->objs.r.x > gen->sizex) ? gen->sizex : gen->objs.r.x;
	gen->objs.r.y = (gen->objs.r.y > gen->sizey) ? gen->sizey : gen->objs.r.y;
	gen->img.img = mlx_new_image(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y);
	gen->img.addr = mlx_get_data_addr(gen->img.img, &(gen->img.bits_per_pixel),
	&(gen->img.line_length), &(gen->img.endian));
	if (sav)
		save_pic(gen, (!gen->objs.c) ? 0 : gen->objs.c->content);
	else
	{
		gen->mlx.win = mlx_new_window(gen->mlx.ptr,
		gen->objs.r.x, gen->objs.r.y, "miniRT");
		print_pic(gen, (!gen->objs.c) ? 0 : gen->objs.c->content);
		mlx_hook(gen->mlx.win, 2, 1L << 0, press_keys, gen);
		mlx_hook(gen->mlx.win, 33, 1L << 17, exit_program, gen);
	}
}

int		main(int argc, char **argv)
{
	t_general	gen;

	gen.cl = 0;
	gen.num_cam = 0;
	gen.savename = 0;
	if (argc < 2 || argc > 3)
		return (errors_mes(1, 0));
	if (argc == 3)
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
			return (errors_mes(6, 0));
		else if (!(gen.savename = create_bmp_name(argv[1])))
			return (errors_mes(7, 0));
	}
	if (parse_file(&(gen.objs), argv[1]))
		return (0);
	start_create(&gen, (argc == 3) ? 1 : 0);
	mlx_loop(gen.mlx.ptr);
	free_gen(&gen, (argc == 3) ? 1 : 2);
}
