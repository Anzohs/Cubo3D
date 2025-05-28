/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 21:28:48 by malourei          #+#    #+#             */
/*   Updated: 2024/04/18 20:33:15 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_total_len(char const *s1, char const *s2)
{
	int	total;

	total = ft_strlen(s1) + ft_strlen(s2);
	return (total);
}

static char	*ft_strcat(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = malloc((sizeof(char) * ft_total_len(s1, s2)) + 1);
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		j++;
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	str = ft_strcat(s1, s2);
	return (str);
}
