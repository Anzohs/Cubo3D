/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 19:25:47 by malourei          #+#    #+#             */
/*   Updated: 2025/05/26 10:23:42 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count(char const *s, char c)
{
	int		i;
	size_t	count;
	int		aspas;

	i = 0;
	count = 0;
	aspas = 0;
	while (s[i] != '\0')
	{
		if (s[i] == 39)
			aspas = !aspas;
		if (((s[i] != c && s[i] != '\t') && (s[i + 1] == c || s[i + 1] == '\0'
					|| s[i + 1] == '\t')) && !aspas)
			count++;
		if (aspas == 1 && s[i + 1] == '\0')
			count++;
		while (s[i] == c && s[i + 1] == c && s[i] == 9 && s[i + 1] == 9
			&& !aspas)
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

static char	*ft_split_help(const char *str, size_t i, size_t j)
{
	size_t	start;
	size_t	len;

	start = j;
	len = i - j;
	if (str[start] == 39)
	{
		start++;
		len--;
	}
	if (str[i - 1] == 39)
		len--;
	return (ft_substr(str, start, len));
}

static void	ft_help_2(t_split *split, char const *s, char c, size_t k)
{
	size_t	j;
	int		aspas;

	aspas = 0;
	while ((s[split->i] == c || s[split->i] == '\t') && s[split->i] != '\0')
		split->i++;
	j = split->i;
	while (((s[split->i] != c && s[split->i] != '\t')
			|| aspas) && s[split->i] != '\0')
	{
		if (s[split->i] == 39)
			aspas = !aspas;
		split->i++;
	}
	split->strs[k] = ft_split_help(s, split->i, j);
}

char	**ft_split(char const *s, char c)
{
	t_split	split;
	size_t	k;

	if (s == NULL)
		return (NULL);
	split.strs = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (!split.strs)
		return (NULL);
	split.i = 0;
	k = 0;
	while (k < ft_count(s, c))
	{
		ft_help_2(&split, s, c, k);
		if (split.strs[k] == NULL)
		{
			ft_split_free(split.strs, k);
			return (NULL);
		}
		k++;
	}
	split.strs[k] = NULL;
	return (split.strs);
}
