/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:49:19 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 05:19:55 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->config->forks[1]);
	if (DEBUG)
		ft_say(philo->config, philo->philo_id, "has taken a lfork");
	else
		ft_say(philo->config, philo->philo_id, "has taken a fork");
	sem_wait(philo->config->forks[1]);
	if (DEBUG)
		ft_say(philo->config, philo->philo_id, "has taken a rfork");
	else
		ft_say(philo->config, philo->philo_id, "has taken a fork");
	ft_say(philo->config, philo->philo_id, "is eating");
	sem_wait(&philo->config->semaphores->last_meal_semaphore);
	philo->last_meal = ft_get_timestamp();
	sem_post(&philo->config->semaphores->last_meal_semaphore);
	sem_wait(&philo->config->semaphores->nb_eat_semaphore);
	philo->nb_eat++;
	sem_post(&philo->config->semaphores->nb_eat_semaphore);
	ft_sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	sem_post(philo->config->forks[1]);
	sem_post(philo->config->forks[1]);
}
