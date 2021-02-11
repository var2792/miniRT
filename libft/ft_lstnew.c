/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 13:19:15 by tarneld           #+#    #+#             */
/*   Updated: 2020/11/03 13:19:33 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list				*ft_lstnew(void *content)
{
	t_list *temp;

	if (!(temp = malloc(sizeof(t_list))))
		return (NULL);
	temp->content = content;
	temp->next = NULL;
	return (temp);
}
