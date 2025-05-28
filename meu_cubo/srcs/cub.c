/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:38:53 by malourei          #+#    #+#             */
/*   Updated: 2025/05/27 18:26:33 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_values(t_map *map)
{
	map->coor_c = NULL;
	map->coor_f = NULL;
	map->textures.tex_ea = NULL;
	map->textures.tex_so = NULL;
	map->textures.tex_we = NULL;
	map->textures.tex_no = NULL;
	map->val_map.strs = NULL;
	map->val_map.count_c = 0;
	map->val_map.count_f = 0;
	map->val_map.count_we = 0;
	map->val_map.count_ea = 0;
	map->val_map.count_no = 0;
	map->val_map.count_so = 0;
	map->textures.fd_ea = 0;
	map->textures.fd_so = 0;
	map->textures.fd_we = 0;
	map->textures.fd_no = 0;
}

int	main(int argc, char *argv[])
{
	int		fd;
	t_map	map;

	if (validate_args(argc, argv) != 1)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(1, "ERROR\nCannot open the map!\n", 27);
		return (1);
	}
	init_values(&map);
	printf("EU sei\n");
	validate_color(fd, &map);
	printf("Texture WE: %s\n", map.textures.tex_we);
	printf("Texture SO: %s\n", map.textures.tex_so);
	printf("Texture EA: %s\n", map.textures.tex_ea);
	printf("Texture NO: %s\n", map.textures.tex_no);
	printf("C: %s\n", map.coor_c[0]);
	printf("F: %s\n", map.coor_f[0]);
	printf("ARGC: %d\nARGV: %s\n", argc, argv[1]);
	ft_close(fd);
	clean(&map);
	return (0);
}
