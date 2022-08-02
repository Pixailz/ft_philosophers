/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:43:20 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 22:52:35 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_config(t_main *config, char **argv)
{
	config->number_of_philosophers = ft_atol(argv[1]);
	config->time_to_die = ft_atol(argv[2]);
	config->time_to_eat = ft_atol(argv[3]);
	config->time_to_sleep = ft_atol(argv[4]);
	if (config->have_max_eat)
		config->max_eat = ft_atol(argv[5]);
	if (DEBUG)
		debug_print_initial_config(config);
}

int	init_entry(t_main *config, char **argv)
{
	init_config(config, argv);
	return (0);
}
