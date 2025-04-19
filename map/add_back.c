/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 20:10:55 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 20:10:57 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	add_back(t_node **head, t_node *n)
{
	t_node	*tmp;

	if (!head || !*head)
		return (*head = n, (void)*head);
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = n;
}
