/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 21:32:48 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/31 20:25:52 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	say_dead(t_philo *philo)
{
	t_stamp	current_ts;

	sem_post(philo->config->s_have_died);
	current_ts = ft_get_timestamp_ms() - philo->config->start_ts;
	sem_wait(philo->config->s_speak);
	if (DEBUG)
		debug_print_elapsed(current_ts);
	else
		printf("%lld", current_ts);
	printf(" %d ", philo->philo_id);
	printf("%s\n", "died");
	exit(1);
}

void	death_check(t_philo *philo)
{
	t_stamp	current_ts;

	sem_wait(philo->config->s_last_meal);
	current_ts = ft_get_timestamp_ms() - philo->last_meal;
	sem_post(philo->config->s_last_meal);
	if (current_ts >= philo->config->time_to_die)
	{
		sem_wait(philo->config->s_have_died);
		philo->have_died = 1;
		sem_post(philo->config->s_have_died);
		say_dead(philo);
	}
}

void	check_all_good(t_philo *philo)
{
	death_check(philo);
	if (philo->config->have_max_eat)
	{
		if (philo->nb_eat == philo->config->max_eat)
		{
			free_entry(philo->config);
			exit(2);
		}
	}
}
