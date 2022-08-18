/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 23:31:21 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/17 21:29:48 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->config->s_take_fork);
	sem_wait(philo->config->s_forks);
	say(philo, "has taken a fork");
	sem_wait(philo->config->s_forks);
	say(philo, "has taken a fork");
	sem_post(philo->config->s_take_fork);
}

void	eat(t_philo *philo)
{
	take_forks(philo);
	say(philo, "is eating");
	sem_wait(philo->config->s_last_meal);
	philo->last_meal = ft_get_timestamp_ms();
	sem_post(philo->config->s_last_meal);
	sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	if (philo->config->have_max_eat)
	{
		sem_wait(philo->config->s_nb_eat);
		philo->nb_eat++;
		sem_post(philo->config->s_nb_eat);
	}
	sem_post(philo->config->s_forks);
	sem_post(philo->config->s_forks);
}
