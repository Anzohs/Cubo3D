/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_color.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:44:16 by malourei          #+#    #+#             */
/*   Updated: 2025/05/28 18:42:10 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_str(char **strs)
{
	int i;

	i = 0;
	while (strs[i] != NULL)
	{
		printf("ST: %s\n", strs[i]);
		i++;
	}
}

static void	val_split_space(t_map *map, char *tmp)
{
	map->val_map.strs = ft_split(tmp, ' ');
	if (!map->val_map.strs)
	{
		write(1, "ERROR\nSplit copy color...\n", 26);
		free(tmp);
		exit(1);
	}
	if (map->val_map.strs[0][0] == 'C' && map->val_map.count_c++)
	{
		write(1, "ERROR\nDuplicate C color definition\n", 35);
		clear_strs(map->val_map.strs);
		free(tmp);
		clean(map);
		exit(1);
	}
	if (map->val_map.strs[0][0] == 'F' && map->val_map.count_f++)
	{
		write(1, "ERROR\nDuplicate F color definition\n", 35);
		clear_strs(map->val_map.strs);
		free(tmp);
		clean(map);
		exit(1);
	}
}

static void	val_join_str(t_map *map, char **str)
{
	int		i;
	char	*joined;

	i = 1;
	joined = NULL;
	while (map->val_map.strs[i])
	{
		if (!*str)
			*str = ft_strdup(map->val_map.strs[i]);
		else
		{
			joined = ft_strjoin(*str, map->val_map.strs[i]);
			if (!joined)
			{
				write(1, "ERROR\nJoin failed!\n", 19);
				clear_strs(map->val_map.strs);
				free(*str);
				exit (1);
			}
			free(*str);
			*str = joined;
		}
		i++;
	}
}

void teste_ze(t_map *map, char *tmp, char **str)
{
	int		i;
	char	*joined;
	char	*joinin;

	i = 0;
	joined = NULL;
	joinin = NULL;
	map->val_map.strs = ft_split(tmp, ',');
	if (!map->val_map.strs)
	{
		write(1, "Deu merda\n", 10);
		exit(1);
	}
	while (map->val_map.strs[i])
	{
		if (!*str)
			*str = ft_strdup(map->val_map.strs[i]);
		else
		{
			joined = ft_strjoin(*str, map->val_map.strs[i]);
			if (!joined)
			{
				write(1, "ERROR\nJoin failed!\n", 19);
				clear_strs(map->val_map.strs);
				free(*str);
				exit (1);
			}
			free(*str);
			*str = joined;
		}
		i++;
	}
	clear_strs(map->val_map.strs);
	printf("ZE: %s\n", *str);
	joinin = *str;
	if (joinin[0] == 'F' && ++map->val_map.count_f)
	{
		joinin++;
		map->coor_f = ft_split(joinin, ' ');
		if (!map->coor_f)
		{
			write(1, "ERROR\nSplit F!\n", 15);
			exit(1);
		}
	}
	else if (joinin[0] == 'C' && ++map->val_map.count_c)
	{
		joinin++;
		map->coor_c = ft_split(joinin, ' ');
		if (!map->coor_c)
		{
			write(1, "ERROR\nSplit C!\n", 15);
			exit(1);
		}
	}
	print_str(map->coor_f);
	printf("ZE2: %s\n", map->coor_f[1]);
	// ver porque vai nulo para
	if (len_strs(map->coor_f) > 3 || len_strs(map->coor_c) > 3)
	{
		print_str(map->coor_f);
		write(1, "ERROR\nInvalid len C or F!\n", 26);
		exit(1);
	}
	if (map->val_map.count_c > 0 || map->val_map.count_f > 0)
	{
		write(1, "ERROR\nSome C or F is duplicate!\n", 32);
	}
	exit(1);
	//map->val_map.strs = ft_split(*str, ' ');
	//print_str(map->val_map.strs);
}

static void	validate_coor_help(t_map *map, char *tmp, char *str)
{
	teste_ze(map, tmp, &str);
	val_split_space(map, tmp);
	val_join_str(map, &str);
	if (str[ft_strlen(str) - 2] == ',')
	{
		write(1, "ERROR\nTo much things!\n", 22);
		free(str);
		free(tmp);
		clear_strs(map->val_map.strs);
		clean(map);
		exit(1);
	}
	if (map->val_map.strs[0][0] == 'C')
		map->coor_c = ft_split(str, ',');
	else
		map->coor_f = ft_split(str, ',');
	free(str);
	str = NULL;
	clear_strs(map->val_map.strs);
}

void	validate_color(int fd, t_map *map)
{
	char	*tmp;
	char	*str;
	char	*tmp2;

	tmp2 = get_next_line(fd);
	str = NULL;
	while (tmp2 != NULL)
	{
		tmp = tmp2;
		while ((*tmp == ' ' || *tmp == '\t') && *(tmp + 1) != '\0')
			tmp++;
		if ((*tmp == 'C' || *tmp == 'F') && (*(tmp + 1) == ' '
				|| *(tmp + 1) == '\t'))
			validate_coor_help(map, tmp, str);
		if (!ft_strncmp(tmp, "NO", 2) || !ft_strncmp(tmp, "WE", 2)
			|| !ft_strncmp(tmp, "SO", 2) || !ft_strncmp(tmp, "EA", 2))
			validate_map(map, tmp, tmp2);
		free(tmp2);
		tmp2 = get_next_line(fd);
	}
	if (!validate_rgb(map))
	{
		clean(map);
		exit (1);
	}
}
