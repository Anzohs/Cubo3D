/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 19:12:28 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/15 19:59:50 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBO_H
# define CUBO_H

# if defined(__APPLE__) && defined(__MACH__)
#  include "mlx/mlx.h"
# else
#  include "mlx_linux/mlx.h"
# endif

# include "libft/libft.h"

# if defined(__APPLE__) && defined(__MACH__)
#  define LEFT_KEY				123	
#  define RIGHT_KEY				124	
#  define UP_KEY				126
#  define DOWN_KEY				125	
#  define A_KEY					0
#  define S_KEY					1
#  define D_KEY					2
#  define W_KEY					13
#  define ESC 					53
# else
#  define LEFT_KEY				65361
#  define RIGHT_KEY				65363
#  define UP_KEY				65362
#  define DOWN_KEY				65364
#  define A_KEY					97
#  define W_KEY					119
#  define S_KEY					115
#  define D_KEY					100
#  define ESC					65307
# endif

#endif
