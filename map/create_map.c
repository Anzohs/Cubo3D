/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:20:41 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 19:20:42 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_map	*create_map(int size)
{
	t_map	*map;

	if (size <= 0)
		return (NULL);
	map = calloc(sizeof(t_map), 1);
	map->size = size;
	if (!map)
		return (NULL);
	map->node = ft_calloc(sizeof(t_node *), size);
	if (!map->node)
		return (free(map), NULL);
	return (map);
}
