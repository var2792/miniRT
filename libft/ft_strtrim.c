/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 13:30:07 by tarneld           #+#    #+#             */
/*   Updated: 2020/10/31 13:30:17 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_simbol(const char c, const char *set)
{
	int i;

	i = 0;
	while (set[i])
		if (c == set[i++])
			return (1);
	return (0);
}

static int	pre_num_set(const char *s1, const char *set)
{
	int i;

	i = 0;
	while (s1[i] != '\0' && is_simbol(s1[i], set))
		i++;
	return (i);
}

static int	suf_num_set(const char *s1, const char *set)
{
	int i;
	int len;

	len = ft_strlen(s1);
	i = len - 1;
	while (s1[i] && is_simbol(s1[i], set))
		i--;
	return (len - i - 1);
}

static char	*copy_str(const char *s1)
{
	int		j;
	int		len;
	char	*res;

	len = ft_strlen(s1);
	if (!(res = malloc(sizeof(char) * len)))
		return (NULL);
	j = -1;
	while (++j < len)
		res[j] = s1[j];
	res[j] = '\0';
	return (res);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	lst;
	char	*res;

	if (!s1)
		return (NULL);
	if (!set)
		return (copy_str(s1));
	lst = ft_strlen(s1) - suf_num_set(s1, set);
	i = pre_num_set(s1, set);
	if (i == ft_strlen(s1))
	{
		if (!(res = malloc(sizeof(char) * 1)))
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (!(res = malloc(sizeof(char) * (lst - i + 1))))
		return (NULL);
	j = 0;
	while (i < lst)
		res[j++] = s1[i++];
	res[j] = '\0';
	return (res);
}
