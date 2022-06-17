/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:43:49 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 01:11:28 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parse_is_good_int(char *to_test)
{
	long	tmp;

	tmp = ft_atol(to_test);
	return (tmp > INT_MAX || tmp < INT_MIN);
}

int	parse(t_main *config, char **argv)
{
	if (parse_is_good_int(argv[1]))
		return (1);
	config->numbers_of_philosophers = ft_atol(argv[1]);
	if (parse_is_good_int(argv[2]))
		return (2);
	config->time_to_die = ft_atol(argv[2]);
	if (parse_is_good_int(argv[3]))
		return (3);
	config->time_to_eat = ft_atol(argv[3]);
	if (parse_is_good_int(argv[4]))
		return (4);
	config->time_to_sleep = ft_atol(argv[4]);
	if (config->have_max_eat)
	{
		if (parse_is_good_int(argv[5]))
			return (5);
		config->number_of_times_each_philosophers_must_eat = ft_atol(argv[5]);
	}
	return (0);
}
