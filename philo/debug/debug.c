/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:54:52 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/28 20:12:10 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_debug_print_initial(t_main *config)
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
		printf("    number_of_times_each_philosophers_must_eat..%d\n", \
							config->number_of_times_each_philosophers_must_eat);
}
