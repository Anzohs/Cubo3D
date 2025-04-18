/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 22:05:07 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 22:05:08 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "libft/libft.h"
# include "structs.h"
# include <time.h>

// delta time used in games
double		get_delta_time(void);
t_game		*inti_game(void);
int			exit_t(t_game *game);
void		key_released(t_game *g);
void		key_pressed(t_game *g);
void		event_handler(t_game *game);
t_player	*p(void);

#endif
