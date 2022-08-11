/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solitary_life_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 06:30:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/11 04:03:19 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	solo_life(t_philo *philo)
{
	sem_wait(philo->config->s_forks);
	say(philo, "has taken a fork");
	sleep_ng(philo->last_meal, philo->config->time_to_die);
	say(philo, "has died");
	sem_post(philo->config->s_forks);
	return (1);
}

int	solo_life_manager(t_main *config)
{
	t_stamp	begin;

	begin = ft_get_timestamp_ms();
	config->start_ts = begin;
	config->philos[0]->last_meal = begin;
	config->philo_pid_table[0] = fork();
	if (config->philo_pid_table[0] == -1)
		return (1);
	else
		solo_life(config->philos[0]);
	return (0);
}
