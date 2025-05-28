/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:54:01 by malourei          #+#    #+#             */
/*   Updated: 2025/05/27 18:10:27 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	select_texture(t_map *map, char **strs)
{
	if (strs[0][0] == 'N' && ++map->val_map.count_no)
		map->textures.tex_no = ft_strdup(strs[1]);
	else if (strs[0][0] == 'W' && ++map->val_map.count_we)
		map->textures.tex_we = ft_strdup(strs[1]);
	else if (strs[0][0] == 'E' && ++map->val_map.count_ea)
		map->textures.tex_ea = ft_strdup(strs[1]);
	else if (strs[0][0] == 'S' && ++map->val_map.count_so)
		map->textures.tex_so = ft_strdup(strs[1]);
}

static void	clean_same(t_map *map, char **strs, char *fre, int fd)
{
	clear_strs(strs);
	free(fre);
	clean(map);
	ft_close(fd);
	exit(1);
}

static char	**validations(t_map *map, char *str, char *fre, int fd)
{
	char	**strs;

	strs = ft_split(str, ' ');
	if (len_strs(strs) == 1)
	{
		clear_strs(strs);
		strs = ft_split(str, 9);
	}
	if (!strs)
	{
		write(1, "ERROR\nSplit texture...\n", 23);
		exit(1);
	}
	if (strs[0][2])
	{
		write(1, "ERROR\nInvalid texture identifier name!\n", 39);
		clean_same(map, strs, fre, fd);
	}
	if (len_strs(strs) != 2)
	{
		write(1, "ERROR\nWrong texture path!\n", 26);
		clean_same(map, strs, fre, fd);
	}
	return (strs);
}

static void	check_dups(t_map *map, char **strs, char *fre, int fd)
{
	char	c;

	c = strs[0][0];
	if ((c == 'E' && map->val_map.count_ea > 0)
		|| (c == 'W' && map->val_map.count_we > 0)
		|| (c == 'S' && map->val_map.count_so > 0)
		|| (c == 'N' && map->val_map.count_no > 0))
	{
		write(1, "ERROR\nDuplicate texture!\n", 25);
		clean_same(map, strs, fre, fd);
	}
}

void	fd_texture(t_map *map, char **strs, int fd)
{
	char	c;

	c = strs[0][0];
	if (c == 'E')
		map->textures.fd_ea = fd;
	else if (c == 'W')
		map->textures.fd_we = fd;
	else if (c == 'S')
		map->textures.fd_so = fd;
	else if (c == 'N')
		map->textures.fd_no = fd;
}

void	validate_map(t_map *map, char *str, char *fre)
{
	char	**strs;
	int		fd;
	size_t	len;

	strs = NULL;
	fd = -1;
	strs = validations(map, str, fre, fd);
	len = ft_strlen(strs[1]);
	strs[1][len - 1] = '\0';
	fd = open(strs[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR\nFailed to open texture!\n", 30);
		clean_same(map, strs, fre, fd);
	}
	check_dups(map, strs, fre, fd);
	select_texture(map, strs);
	fd_texture(map, strs, fd);
	clear_strs(strs);
}
