/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:36:48 by malourei          #+#    #+#             */
/*   Updated: 2025/05/29 23:17:15 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char ch)
{
	return (ch == ' ' || ch == ',');
}

static size_t	ft_count(char const *s)
{
	int		i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (!is_sep(s[i]) && (is_sep(s[i + 1]) || s[i + 1] == '\0'))
			count++;
		while (is_sep(s[i]) && is_sep(s[i + 1]))
			i++;
		i++;
	}
	return (count);
}

static void	ft_split_free(char **strs, size_t len)
{
	size_t	i;

	i = 0;
	while (len > i)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

static char	**ft_split_help(char **strs, char const *s)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (k < ft_count(s))
	{
		while (is_sep(s[i]) && s[i] != '\0')
			i++;
		j = i;
		while (!is_sep(s[i]) && s[i] != '\0')
			i++;
		strs[k] = ft_substr(s, j, (i - j));
		if (!strs[k])
		{
			ft_split_free(strs, k);
			return (NULL);
		}
		while (is_sep(s[i]))
			i++;
		k++;
	}
	strs[k] = NULL;
	return (strs);
}

char	**ft_split_new(char const *s)
{
	char	**strs;
	size_t	len_s;

	if (s == NULL)
		return (NULL);
	len_s = ft_count(s);
	strs = malloc(sizeof(char *) * (len_s + 1));
	if (!strs)
		return (NULL);
	ft_split_help(strs, s);
	return (strs);
}
