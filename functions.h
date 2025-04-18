#ifndef FUNCTIONS_H
# define FUNCTIONS_H

#include <time.h>
#include "libft/libft.h"
#include "structs.h"


//delta time used in games
double	get_delta_time(void);
t_game	*inti_game(void);
int	exit_t(t_game *game);
void	key_released(t_game *g);
void	key_pressed(t_game *g);
void	event_handler(t_game *game);
t_player	*p(void);

#endif
