/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42lisboa.pt>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 23:39:05 by malourei          #+#    #+#             */
/*   Updated: 2025/05/27 18:26:55 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_validate_map
{
	int		count_f;
	int		count_c;
	int		count_we;
	int		count_ea;
	int		count_so;
	int		count_no;
	char	**strs;
}	t_validate_map;

typedef struct s_texture
{
	char	*tex_we;
	char	*tex_ea;
	char	*tex_so;
	char	*tex_no;
	int		fd_we;
	int		fd_ea;
	int		fd_so;
	int		fd_no;
}	t_texture;

typedef struct s_map
{
	char			**coor_c;
	char			**coor_f;
	//int				fd_map;
	t_validate_map	val_map;
	t_texture		textures;
}	t_map;

int		validate_args(int argc, char **argv);
void	validate_map(t_map *map, char *str, char *fre);
void	clear_strs(char **strs);
void	clean(t_map *map);
void	validate_color(int fd, t_map *map);
int		len_strs(char **strs);
int		validate_rgb(t_map *map);
long	ft_atol(const char *nptr);
void	ft_close(int fd);
void	close_fds(t_map *map);

#endif
