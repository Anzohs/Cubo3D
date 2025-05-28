/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malourei <malourei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:33:52 by malourei          #+#    #+#             */
/*   Updated: 2024/04/12 22:33:52 by malourei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(long number)
{
	int	count;

	count = 0;
	if (number <= 0)
	{
		count++;
		number *= -1;
	}
	while (number > 0)
	{
		number /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		i;
	int		length;
	char	*array;
	long	number;

	i = 0;
	number = (long)n;
	length = ft_intlen(number);
	array = malloc((sizeof(char) * length) + 1);
	if (!array)
		return (NULL);
	if (number < 0)
	{
		number *= -1;
		array[i] = '-';
		i++;
	}
	array[length] = '\0';
	while (length > i)
	{
		length--;
		array[length] = ((number % 10) + '0');
		number /= 10;
	}
	return (array);
}
