/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 22:24:52 by malourei          #+#    #+#             */
/*   Updated: 2025/05/27 18:24:32 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	clear_strs(char **strs)
{
	int	i;

	if (!strs)
		return ;
	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

void	ft_close(int fd)
{
	if (fd > 0 && fd != STDERR_FILENO && fd != STDIN_FILENO
		&& fd != STDOUT_FILENO)
		close (fd);
}

void	close_fds(t_map *map)
{
	ft_close(map->textures.fd_ea);
	ft_close(map->textures.fd_no);
	ft_close(map->textures.fd_so);
	ft_close(map->textures.fd_we);
}

void	clean(t_map *map)
{
	clear_strs(map->coor_c);
	clear_strs(map->coor_f);
	free(map->textures.tex_ea);
	free(map->textures.tex_no);
	free(map->textures.tex_so);
	free(map->textures.tex_we);
	close_fds(map);
}
