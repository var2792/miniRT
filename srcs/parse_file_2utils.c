/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_2utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int	parse_sphere(char **line, t_scobjs *scene)
{
	t_sphere	*cont;
	t_list		*new;

	(*line) += 2;
	if (!(cont = malloc(sizeof(*cont))))
		return (errors_mes(7, 0));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1)
	|| sep_fl(&(cont->cd.z), line, 1))
		return (1);
	cont->d = ft_atoi_float(line);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1)
	|| sep_fl(&(cont->cl.z), line, 1))
		return (1);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->sp), new);
	return (0);
}

int	parse_plane(char **line, t_scobjs *scene)
{
	t_plane	*cont;
	t_list	*new;

	(*line) += 2;
	if (!(cont = malloc(sizeof(*cont))))
		return (errors_mes(7, 0));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1)
	|| sep_fl(&(cont->cd.z), line, 1))
		return (1);
	if (sep_fl(&(cont->nm.x), line, 0) || sep_fl(&(cont->nm.y), line, 1)
	|| sep_fl(&(cont->nm.z), line, 1))
		return (1);
	if (check_normal(cont->nm))
		return (1);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1)
	|| sep_fl(&(cont->cl.z), line, 1))
		return (1);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->pl), new);
	return (0);
}

int	parse_square(char **line, t_scobjs *scene)
{
	t_square	*cont;
	t_list		*new;

	(*line) += 2;
	if (!(cont = malloc(sizeof(*cont))))
		return (errors_mes(7, 0));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1)
	|| sep_fl(&(cont->cd.z), line, 1))
		return (1);
	if (sep_fl(&(cont->nm.x), line, 0) || sep_fl(&(cont->nm.y), line, 1)
	|| sep_fl(&(cont->nm.z), line, 1))
		return (1);
	if (check_normal(cont->nm))
		return (1);
	cont->s = ft_atoi_float(line);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1)
	|| sep_fl(&(cont->cl.z), line, 1))
		return (1);
	if (check_color(cont->cl))
		return (1);
	find_point_sq(*cont, &(cont->ps));
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->sq), new);
	return (0);
}

int	parse_cylinder(char **line, t_scobjs *scene)
{
	t_cylinder	*cont;
	t_list		*new;

	(*line) += 2;
	if (!(cont = malloc(sizeof(*cont))))
		return (errors_mes(7, 0));
	if (sep_fl(&(cont->cd.x), line, 0) || sep_fl(&(cont->cd.y), line, 1)
	|| sep_fl(&(cont->cd.z), line, 1))
		return (1);
	if (sep_fl(&(cont->nm.x), line, 0) || sep_fl(&(cont->nm.y), line, 1)
	|| sep_fl(&(cont->nm.z), line, 1))
		return (1);
	if (check_normal(cont->nm))
		return (1);
	cont->d = ft_atoi_float(line);
	cont->h = ft_atoi_float(line);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1)
	|| sep_fl(&(cont->cl.z), line, 1))
		return (1);
	if (check_color(cont->cl))
		return (1);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->cy), new);
	return (0);
}

int	parse_triangle(char **line, t_scobjs *scene)
{
	t_triangle	*cont;
	t_list		*new;

	(*line) += 2;
	if (!(cont = malloc(sizeof(*cont))))
		return (errors_mes(7, 0));
	if (sep_fl(&(cont->cd1.x), line, 0) || sep_fl(&(cont->cd1.y), line, 1)
	|| sep_fl(&(cont->cd1.z), line, 1))
		return (1);
	if (sep_fl(&(cont->cd2.x), line, 0) || sep_fl(&(cont->cd2.y), line, 1)
	|| sep_fl(&(cont->cd2.z), line, 1))
		return (1);
	if (sep_fl(&(cont->cd3.x), line, 0) || sep_fl(&(cont->cd3.y), line, 1)
	|| sep_fl(&(cont->cd3.z), line, 1))
		return (1);
	if (sep_fl(&(cont->cl.x), line, 0) || sep_fl(&(cont->cl.y), line, 1)
	|| sep_fl(&(cont->cl.z), line, 1) || check_color(cont->cl))
		return (1);
	cont->nm = cross_prv(sum_vs(1, cont->cd1, -1, cont->cd2),
	sum_vs(1, cont->cd2, -1, cont->cd3));
	cont->nm = sum_vs(1 / len_vec(cont->nm), cont->nm, 0, cont->nm);
	new = ft_lstnew(cont);
	ft_lstadd_back(&(scene->tr), new);
	return (0);
}
