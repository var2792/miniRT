/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

void	next_cam(t_general *gen)
{
	t_list	*next;

	if ((next = ft_lstnum(gen->objs.c, gen->num_cam + 1)) != NULL)
	{
		gen->num_cam += 1;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		free_gen(gen, 0);
		print_pic(gen, next->content);
	}
	else
	{
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		free_gen(gen, 0);
		gen->num_cam = 0;
		next = ft_lstnum(gen->objs.c, gen->num_cam);
		print_pic(gen, next->content);
	}
}

void	prew_cam(t_general *gen)
{
	t_list	*next;

	if ((next = ft_lstnum(gen->objs.c, gen->num_cam - 1)) != NULL)
	{
		gen->num_cam -= 1;
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		free_gen(gen, 0);
		print_pic(gen, next->content);
	}
	else
	{
		mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
		free_gen(gen, 0);
		gen->num_cam = ft_lstsize(gen->objs.c) - 1;
		next = ft_lstnum(gen->objs.c, gen->num_cam);
		print_pic(gen, next->content);
	}
}

void	change_cam(int key, t_general *gen)
{
	t_camera*cam;

	cam = ft_lstnum(gen->objs.c, gen->num_cam)->content;
	if (key == 119)
		cam->cd.z += 2;
	if (key == 115)
		cam->cd.z -= 2;
	if (key == 97)
		cam->cd.x -= 2;
	if (key == 100)
		cam->cd.x += 2;
	if (key == 122)
		cam->cd.y += 2;
	if (key == 120)
		cam->cd.y -= 2;
	mlx_clear_window(gen->mlx.ptr, gen->mlx.win);
	print_pic(gen, cam);
}

int		press_keys(int key, t_general *gen)
{
	if (key == 65307)
		return (exit_program(gen));
	if (key == 65363)
		next_cam(gen);
	if (key == 65361)
		prew_cam(gen);
	if (key == 119 || key == 115 || key == 97 ||
	key == 100 || key == 122 || key == 120)
		change_cam(key, gen);
	if (key == 99)
	{
		ft_putstr_fd("Camera's coords: ", 1);
		ft_putnbr_fd(gen->scene.cdo.x, 1);
		ft_putchar_fd('\t', 1);
		ft_putnbr_fd(gen->scene.cdo.y, 1);
		ft_putchar_fd('\t', 1);
		ft_putnbr_fd(gen->scene.cdo.z, 1);
		ft_putchar_fd('\n', 1);
	}
	return (0);
}
