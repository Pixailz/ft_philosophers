/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:49:19 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 09:51:58 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->config->forks[philo->l_fork_id]);
	if (DEBUG)
		ft_say(philo->config, philo->philo_id, "has taken a lfork");
	else
		ft_say(philo->config, philo->philo_id, "has taken a fork");
	pthread_mutex_lock(philo->config->forks[philo->r_fork_id]);
	if (DEBUG)
		ft_say(philo->config, philo->philo_id, "has taken a rfork");
	else
		ft_say(philo->config, philo->philo_id, "has taken a fork");
	ft_say(philo->config, philo->philo_id, "is eating");
	pthread_mutex_lock(&philo->config->mutexs->last_meal_mutex);
	philo->last_meal = ft_get_timestamp();
	pthread_mutex_unlock(&philo->config->mutexs->last_meal_mutex);
	pthread_mutex_lock(&philo->config->mutexs->nb_eat_mutex);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->config->mutexs->nb_eat_mutex);
	ft_sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	pthread_mutex_unlock(philo->config->forks[philo->l_fork_id]);
	pthread_mutex_unlock(philo->config->forks[philo->r_fork_id]);
}
