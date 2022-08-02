/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:20:21 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 23:16:51 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_is_empty(t_main *config, char **argv)
{
	if (!ft_strlen(argv[1]))
		return (1);
	if (!ft_strlen(argv[2]))
		return (2);
	if (!ft_strlen(argv[3]))
		return (3);
	if (!ft_strlen(argv[4]))
		return (4);
	if (config->have_max_eat)
		if (!ft_strlen(argv[5]))
			return (5);
	return (0);
}

int	parse_is_numeric(t_main *config, char **argv)
{
	if (!ft_isnumeric(argv[1]))
		return (6);
	if (!ft_isnumeric(argv[2]))
		return (7);
	if (!ft_isnumeric(argv[3]))
		return (8);
	if (!ft_isnumeric(argv[4]))
		return (9);
	if (config->have_max_eat)
		if (!ft_isnumeric(argv[5]))
			return (10);
	return (0);
}

int	parse_is_good_number(t_main *config, char **argv)
{
	int			counter;
	long int	number_tmp;

	counter = 1;
	while (counter <= 4)
	{
		number_tmp = ft_atol(argv[counter]);
		if (number_tmp < 0)
			return (counter + 10);
		if (number_tmp > INT_MAX)
			return (counter + 15);
		counter++;
	}
	if (config->have_max_eat)
	{
		number_tmp = ft_atol(argv[5]);
		if (number_tmp < INT_MIN)
			return (15);
		if (number_tmp > INT_MAX)
			return (20);
	}
	return (0);
}

int	parse(t_main *config, char **argv)
{
	int	return_code;

	return_code = parse_is_empty(config, argv);
	if (return_code)
		return (return_code);
	return_code = parse_is_numeric(config, argv);
	if (return_code)
		return (return_code);
	return_code = parse_is_good_number(config, argv);
	if (return_code)
		return (return_code);
	return (0);
}
