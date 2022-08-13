/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 03:12:28 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/13 12:46:40 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	check_starving(t_philo *philo)
{
	t_stamp	current_ts;

	current_ts = ft_get_timestamp_ms() - philo->last_meal;
	if (current_ts > philo->config->time_to_die)
	{
		philo->have_died = 1;
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
			if (philo->nb_eat == philo->config->max_eat)
			{
				philo->have_max_eaten = 1;
				break ;
			}
		}
		usleep(CHECK_TIME);
	}
	return (void_philo);
}
