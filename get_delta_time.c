/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_delta_time.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 20:46:01 by hladeiro          #+#    #+#             */
/*   Updated: 2025/04/18 20:46:02 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubo.h"

static double	get_time_in_seconds(void)
{
	struct timespec	ts;

	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec + ts.tv_nsec / 1e9);
}

double	get_delta_time(void)
{
	static double	last_frame;
	double			current;
	double			dt;

	current = get_time_in_seconds();
	dt = current - last_frame;
	last_frame = current;
	return (dt);
}
