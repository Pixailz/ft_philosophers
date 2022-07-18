/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:49:19 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/04 14:04:36 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_eat(t_philo *philo)
{
	sem_wait(philo->config->forks);
	ft_say(philo->config, philo->philo_id, "has taken a fork");
	sem_wait(philo->config->forks);
	ft_say(philo->config, philo->philo_id, "has taken a fork");
	sem_wait(philo->config->check_meal);
	ft_say(philo->config, philo->philo_id, "is eating");
	philo->last_meal = ft_get_timestamp();
	sem_post(philo->config->check_meal);
	sem_wait(philo->config->check_all_ate);
	philo->nb_eat++;
	sem_post(philo->config->check_all_ate);
	ft_sleep_ng(philo, philo->last_meal, philo->config->time_to_eat);
	sem_post(philo->config->forks);
	sem_post(philo->config->forks);
}
