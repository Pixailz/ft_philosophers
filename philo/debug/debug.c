/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:42:25 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 22:54:34 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	debug_print_initial_config(t_main *config)
{
	printf("INITIAL CONFIG\n");
	printf("    number_of_philosophers......................%d\n", \
												config->number_of_philosophers);
	printf("    time_to_die.................................%d\n", \
												config->time_to_die);
	printf("    time_to_eat.................................%d\n", \
												config->time_to_eat);
	printf("    time_to_sleep...............................%d\n", \
												config->time_to_sleep);
	if (config->have_max_eat)
		printf("    max_eat.....................................%d\n", \
															config->max_eat);
}
