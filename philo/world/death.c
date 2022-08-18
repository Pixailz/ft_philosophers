/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 00:04:37 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/18 22:14:35 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	check_starving(t_philo *philo)
{
	t_stamp	current_ts;

	pthread_mutex_lock(&philo->config->m_last_meal);
	current_ts = ft_get_timestamp_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->config->m_last_meal);
	if (current_ts >= philo->config->time_to_die)
	{
		say(philo, "died");
		pthread_mutex_lock(&philo->config->m_have_died);
		philo->config->have_died = 1;
		pthread_mutex_unlock(&philo->config->m_have_died);
	}
}

void	check_all_ate(t_philo *philo, int *nb_eat)
{
	pthread_mutex_lock(&philo->config->m_all_ate);
	pthread_mutex_lock(&philo->config->m_nb_eat);
	if (philo->nb_eat >= philo->config->max_eat)
	{
		philo->have_max_eaten = 1;
		(*nb_eat)++;
	}
	pthread_mutex_unlock(&philo->config->m_nb_eat);
	pthread_mutex_unlock(&philo->config->m_all_ate);
}

void	*death(void *void_config)
{
	t_main	*config;
	int		nb_eat;
	int		counter;

	config = (t_main *)void_config;
	while (!config->have_died && !config->all_ate)
	{
		counter = 0;
		nb_eat = 0;
		while (counter < config->number_of_philosophers)
		{
			check_starving(config->philos[counter]);
			if (config->have_max_eat)
				check_all_ate(config->philos[counter], &nb_eat);
			counter++;
		}
		pthread_mutex_lock(&config->m_all_ate);
		if (nb_eat == config->number_of_philosophers)
			config->all_ate = 1;
		pthread_mutex_unlock(&config->m_all_ate);
	}
	return (void_config);
}
