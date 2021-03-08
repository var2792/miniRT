/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs_selection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/funct_def.h"

int		check_see_objs(t_general gen, t_vector ptr, int num_ob)
{
	int res;

	res = 0;
	if (num_ob > -1 && num_ob < 100)
		res = check_see_sp(gen, ptr, num_ob);
	else
		res = check_see_sp(gen, ptr, -1);
	if (num_ob > 99 && num_ob < 200)
		res = (res == 0) ? check_see_pl(gen, ptr, num_ob - 100) : res;
	else
		res = (res == 0) ? check_see_pl(gen, ptr, -1) : res;
	if (num_ob > 199 && num_ob < 300)
		res = (res == 0) ? check_see_sq(gen, ptr, num_ob - 200) : res;
	else
		res = (res == 0) ? check_see_sq(gen, ptr, -1) : res;
	if (num_ob > 299 && num_ob < 400)
		res = (res == 0) ? check_see_tr(gen, ptr, num_ob - 300) : res;
	else
		res = (res == 0) ? check_see_tr(gen, ptr, -1) : res;
	if (num_ob > 399 && num_ob < 500)
		res = (res == 0) ? check_see_cy(gen, ptr, num_ob - 400) : res;
	else
		res = (res == 0) ? check_see_cy(gen, ptr, -1) : res;
	return (res);
}

float	check_shadow(t_light num_l, int num_ob,
t_scobjs objects, t_vector p)
{
	float	res;
	float	temp;

	res = check_shadow_sp(num_l, (num_ob > -1 && num_ob < 100)
	? num_ob : -1, objects, p);
	temp = check_shadow_pl(num_l, (num_ob > 99 && num_ob < 200)
	? (num_ob - 100) : -1, objects, p);
	res = (temp < res) ? temp : res;
	if (num_ob > 199 && num_ob < 300)
		temp = check_shadow_sq(num_l, (int)(num_ob - 200), objects, p);
	else
		temp = check_shadow_sq(num_l, -1, objects, p);
	res = (temp < res) ? temp : res;
	if (num_ob > 299 && num_ob < 400)
		temp = check_shadow_tr(num_l, (int)(num_ob - 300), objects, p);
	else
		temp = check_shadow_tr(num_l, -1, objects, p);
	res = (temp < res) ? temp : res;
	if (num_ob > 399 && num_ob < 500)
		temp = check_shadow_cy(num_l, (int)(num_ob - 400), objects, p);
	else
		temp = check_shadow_cy(num_l, -1, objects, p);
	res = (temp < res) ? temp : res;
	return (res);
}
