/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pic.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

void	show_null_file(t_general *gen, int sav)
{
	ft_write_xyz(&(gen->pix), 0, 0, 0);
	while (gen->pix.x < gen->objs.r.x)
	{
		while (gen->pix.y < gen->objs.r.y)
		{
			my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, 0);
			gen->pix.y += 1;
		}
		gen->pix.y = 0;
		gen->pix.x += 1;
	}
	if (sav)
	{
		bmp_image(gen);
		exit_program(gen);
		free_gen(gen, 1);
	}
	else
		mlx_put_image_to_window(gen->mlx.ptr, gen->mlx.win, gen->img.img, 0, 0);
}

void	point_with_objs(t_general *gen)
{
	gen->scene.cdv = trans_pixv(*gen);
	gen->cl = -5;
	if (gen->objs.sp != NULL)
		belong_to_sphere(gen, gen->objs.sp->content);
	gen->pix.z = 0;
	if (gen->objs.pl != NULL)
		belong_to_plane(gen, gen->objs.pl->content);
	gen->pix.z = 0;
	if (gen->objs.sq != NULL)
		belong_to_square(gen, gen->objs.sq->content);
	gen->pix.z = 0;
	if (gen->objs.tr != NULL)
		belong_to_triangle(gen, gen->objs.tr->content);
	gen->pix.z = 0;
	if (gen->objs.cy != NULL)
		belong_to_cylinder(gen, gen->objs.cy->content);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	print_pic(t_general *gen, t_camera *cam)
{
	ft_putendl_fd("Started drawing...", 1);
	if (gen->objs.c == NULL)
		return (show_null_file(gen, 0));
	if (parse_put_canvas(&(gen->scene), gen->objs, cam))
		return ;
	ft_write_xyz(&(gen->pix), 0, 0, 0);
	while (gen->pix.x < gen->objs.r.x)
	{
		while (gen->pix.y < gen->objs.r.y)
		{
			point_with_objs(gen);
			if (gen->cl >= 0)
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, gen->cl);
			else
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, 0);
			gen->pix.z = 0;
			gen->pix.y += 1;
		}
		gen->pix.y = 0;
		gen->pix.x += 1;
	}
	mlx_put_image_to_window(gen->mlx.ptr, gen->mlx.win, gen->img.img, 0, 0);
	ft_putendl_fd("Finished drawing.", 1);
}
