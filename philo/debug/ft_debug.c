/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 17:54:52 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 11:25:41 by brda-sil         ###   ########.fr       */
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
		printf("    max_eat..%d\n", config->max_eat);
}

void	ft_debug_print_elapsed(long long elapsed)
{
	long long	sec;
	long long	usec;

	sec = elapsed / 1000;
	usec = elapsed % 1000;
	if (sec)
	{
		printf("%lld.", sec);
		if (usec < 10)
			printf("00%lld", usec);
		else if (usec < 100)
			printf("0%lld", usec);
		else
			printf("%lld", usec);
	}
	else
		printf("%lld", usec);
}
