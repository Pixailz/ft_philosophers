/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:31:21 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/13 10:49:17 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->config->s_forks);
	say(philo, "has taken a fork");
	sem_wait(philo->config->s_forks);
	say(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	say(philo, "is eating");
	philo->last_meal = ft_get_timestamp_ms();
	if (philo->config->have_max_eat)
		philo->nb_eat++;
	sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	sem_post(philo->config->s_forks);
	sem_post(philo->config->s_forks);
	if (philo->config->have_max_eat)
		if (philo->nb_eat == philo->config->max_eat)
			exit(2);
}
