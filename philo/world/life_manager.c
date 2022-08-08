/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:02:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:56:46 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_all_good(t_philo *philo)
{
	if (philo->config->have_max_eat)
	{
		pthread_mutex_lock(&philo->config->m_all_ate);
		if (philo->config->all_ate)
			return (0);
		pthread_mutex_unlock(&philo->config->m_all_ate);
	}
	pthread_mutex_lock(&philo->config->m_have_died);
	if (philo->config->have_died)
		return (0);
	pthread_mutex_unlock(&philo->config->m_have_died);
	return (1);
}

void	cycle_of_life(t_philo *philo)
{
	ft_lock_both(philo->config);
	while (!philo->config->all_ate && !philo->config->have_died)
	{
		ft_unlock_both(philo->config);
		eat(philo);
		if (!check_all_good(philo))
		{
			ft_lock_both(philo->config);
			break ;
		}
		say(philo, "is sleeping");
		sleep_ng(philo, ft_get_timestamp_ms(), philo->config->time_to_sleep);
		say(philo, "is thinking");
		if (philo->config->have_max_eat)
		{
			pthread_mutex_lock(&philo->config->m_all_ate);
			if (philo->have_max_eaten)
			{
				pthread_mutex_unlock(&philo->config->m_all_ate);
				break ;
			}
			pthread_mutex_unlock(&philo->config->m_all_ate);
		}
		ft_lock_both(philo->config);
	}
	ft_unlock_both(philo->config);
}

void	*life(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2)
		usleep(500);
	cycle_of_life(philo);
	return (void_philo);
}

int	life_manager(t_main *config)
{
	int		counter;
	t_stamp	begin;

	begin = ft_get_timestamp_ms();
	config->start_ts = begin;
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = begin;
		if (pthread_create(&config->philos[counter]->thread_id, NULL, \
												life, config->philos[counter]))
			return (1);
		counter++;
	}
	if (pthread_create(&config->death, NULL, death, config))
		return (1);
	if (pthread_join(config->death, NULL))
		return (2);
	counter = 0;
	while (counter < config->number_of_philosophers)
		if (pthread_join(config->philos[counter++]->thread_id, NULL))
			return (2);
	return (0);
}
