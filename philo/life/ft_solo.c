/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:24:32 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 09:51:59 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_solo_live(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	pthread_mutex_lock(philo->config->forks[philo->l_fork_id]);
	if (DEBUG)
		ft_say(philo->config, 1, "has taken a lfork");
	else
		ft_say(philo->config, 1, "has taken a fork");
	ft_sleep_ng(philo, philo->last_meal, philo->config->time_to_die);
	pthread_mutex_unlock(philo->config->forks[philo->l_fork_id]);
	ft_say(philo->config, 1, "died");
	return ((void *)0);
}

int	ft_solo_life_manager(t_main *config)
{
	config->start_timestamp = ft_get_timestamp();
	config->philos[0]->last_meal = ft_get_timestamp();
	if (pthread_create(&config->philos[0]->thread_id, NULL, \
											ft_solo_live, config->philos[0]))
		return (1);
	if (pthread_join(config->philos[0]->thread_id, NULL))
		return (2);
	return (0);
}
