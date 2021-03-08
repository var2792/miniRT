/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnum.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:19:15 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/03 13:19:33 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnum(t_list *lst, int num)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp && i < num)
	{
		if (temp->next == 0)
			break ;
		else
			temp = temp->next;
		i++;
	}
	if (i == num)
		return (temp);
	else
		return (NULL);
}
