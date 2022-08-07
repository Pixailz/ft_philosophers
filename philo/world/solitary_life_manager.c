/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solitary_life_manager.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 06:30:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/07 04:59:20 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*solo_life(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(philo->config->forks[])
	return ((void *) void_philo);
}

int	solo_life_manager(t_main *config)
{
	t_stamp	begin;

	begin = ft_get_timestamp_ms();
	config->start_ts = begin;
	config->philos[0]->last_meal = begin;
	if (pthread_create(&config->philos[0]->thread_id, NULL, \
												solo_life, config->philos[0]))
		return (1);
	if (pthread_join(config->philos[0]->thread_id, NULL))
		return (2);
	return (0);
}
