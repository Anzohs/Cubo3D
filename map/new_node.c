/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:57:53 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 20:11:25 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

t_node	*new_node(int i, t_vector *key)
{
	t_node	*n;

	n = ft_calloc(sizeof(t_node), 1);
	if (!n)
		return (NULL);
	n->key = key;
	n->value = i;
	n->next = NULL;
	return (n);
}
