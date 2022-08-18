/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 03:12:28 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 03:29:21 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_starving(t_philo *philo)
{
	t_stamp	current_ts;

	sem_wait(philo->config->s_last_meal);
	current_ts = ft_get_timestamp_ms() - philo->last_meal;
	sem_post(philo->config->s_last_meal);
	if (current_ts > philo->config->time_to_die)
	{
		sem_wait(philo->config->s_have_died);
		philo->have_died = 1;
		sem_post(philo->config->s_have_died);
		return (1);
	}
	return (0);
}

void	*death(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	while (!philo->have_died && !philo->have_max_eaten)
	{
		if (check_starving(philo))
			break ;
		if (philo->config->have_max_eat)
		{
			sem_wait(philo->config->s_nb_eat);
			if (philo->nb_eat == philo->config->max_eat)
			{
				sem_post(philo->config->s_nb_eat);
				philo->have_max_eaten = 1;
				break ;
			}
			sem_post(philo->config->s_nb_eat);
		}
		usleep(SLEEP_TIME);
	}
	return (void_philo);
}
