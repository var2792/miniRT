/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:22:18 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/03 13:22:19 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*begin;

	begin = lst;
	while (begin)
	{
		(*f)(begin->content);
		begin = begin->next;
	}
}
