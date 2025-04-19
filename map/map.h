/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 19:20:46 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/19 20:02:38 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# include "../libft/libft.h"

typedef struct s_vector
{
	int				x;
	int				y;
}					t_vector;

typedef struct s_node
{
	t_vector		*key;
	int				value;
	struct s_node	*next;
}					t_node;

typedef struct s_map
{
	t_node			**node;
	int				size;
}					t_map;

// map functions!
t_map				*create_map(int size);
void				add_node(t_map **map, int pos, t_node *node);
// node functions
t_node				*new_node(int i, t_vector *key);
void				add_back(t_node **head, t_node *n);
t_node				*get_node(t_node *n, int pos);

#endif
