/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hladeiro <hladeiro@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 22:25:28 by hladeiro          #+#    #+#             */
/*   Updated: 2025/05/29 22:32:15 by hladeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

static bool	validname(t_string str)
{
	return (str[ft_strlen(str) - 1] == 'b' && str[ft_strlen(str) - 2] == 'u'
		&& str[ft_strlen(str) - 3] == 'c' && str[ft_strlen(str) - 4] == '.');
}

int	main(int ac, t_string *av)
{
	t_parsing	*parser;

	if (ac != 2)
		return (printf("invalid args\n"));
	if (ft_strlen(av[1]) <= 4 || !validname(av[1]))
		return (printf("invalid name\n"));
	parser = ft_calloc(sizeof(t_parsing), 1);
	if (!parser)
		return (1);
	free(parser);
}
