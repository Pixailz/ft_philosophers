/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 13:43:49 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 03:47:47 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_parse_is_good_int(char *to_test)
{
	long	tmp;

	tmp = ft_atol(to_test);
	return ((tmp > INT_MAX || tmp < INT_MIN) || (tmp < 0));
}

int	ft_parse_is_numeric(t_main *config, char **argv)
{
	if (!ft_isnum(argv[1]))
		return (1);
	if (!ft_isnum(argv[2]))
		return (2);
	if (!ft_isnum(argv[3]))
		return (3);
	if (!ft_isnum(argv[4]))
		return (4);
	if (config->have_max_eat)
		if (!ft_isnum(argv[5]))
			return (5);
	return (0);
}

int	ft_parse_is_arg_too_big(t_main *config, char **argv)
{
	if (ft_parse_is_good_int(argv[1]))
		return (6);
	config->number_of_philosophers = ft_atol(argv[1]);
	if (ft_parse_is_good_int(argv[2]))
		return (7);
	config->time_to_die = ft_atol(argv[2]);
	if (ft_parse_is_good_int(argv[3]))
		return (8);
	config->time_to_eat = ft_atol(argv[3]);
	if (ft_parse_is_good_int(argv[4]))
		return (9);
	config->time_to_sleep = ft_atol(argv[4]);
	if (config->have_max_eat)
	{
		if (ft_parse_is_good_int(argv[5]))
			return (10);
		config->max_eat = ft_atol(argv[5]);
	}
	return (0);
}

int	ft_parse(t_main *config, char **argv)
{
	int	return_code;

	return_code = ft_parse_is_numeric(config, argv);
	if (return_code)
		return (return_code);
	return_code = ft_parse_is_arg_too_big(config, argv);
	if (return_code)
		return (return_code);
	if (DEBUG)
		ft_debug_print_initial(config);
	return (0);
}
