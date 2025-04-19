/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:03:04 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 20:03:05 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_node	*get_node(t_node *n, int pos)
{
	int		i;
	t_node	*tmp;

	i = -1;
	tmp = n;
	while (tmp && ++i != pos)
		tmp = tmp->next;
	return (tmp);
}
