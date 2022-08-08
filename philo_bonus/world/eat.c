/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:31:21 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:36:28 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->config->forks[philo->l_fork_id]);
	if (DEBUG)
		say(philo, "has taken lfork");
	else
		say(philo, "has taken a fork");
	pthread_mutex_lock(philo->config->forks[philo->r_fork_id]);
	if (DEBUG)
		say(philo, "has taken rfork");
	else
		say(philo, "has taken a fork");
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	say(philo, "is eating");
	pthread_mutex_lock(&philo->config->m_last_meal);
	philo->last_meal = ft_get_timestamp_ms();
	pthread_mutex_unlock(&philo->config->m_last_meal);
	if (philo->config->have_max_eat)
	{
		pthread_mutex_lock(&philo->config->m_nb_eat);
		philo->nb_eat++;
		pthread_mutex_unlock(&philo->config->m_nb_eat);
	}
	sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	pthread_mutex_unlock(philo->config->forks[philo->l_fork_id]);
	pthread_mutex_unlock(philo->config->forks[philo->r_fork_id]);
}
