/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:57:33 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 19:59:21 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	add_node(t_map **map, int pos, t_node *node)
{
	if (pos > (*map)->size)
		return ;
	add_back(&(*map)->node[pos], node);
}
