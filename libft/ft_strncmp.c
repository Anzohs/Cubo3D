/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 19:18:27 by hladeiro          #+#    #+#             */
/*   Updated: 2025/06/12 09:34:31 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] == s2[i] && i < n && s1[i] && s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strncmp_reverse(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		j;

	i = ft_strlen(s1) - 1;
	j = (int)n - 1;
	while (j >= 0)
	{
		if (s1[i] != s2[j])
			return (1);
		i--;
		j--;
	}
	return (0);
}
