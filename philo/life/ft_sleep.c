/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:55:14 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 09:58:45 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep_ng(t_philo *philo, long long begin, long long time_to_wait)
{
	long long	current_time;

	pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		pthread_mutex_unlock(&philo->config->mutexs->died_all_ate_mutex);
		current_time = ft_get_timestamp();
		if (current_time - begin >= time_to_wait)
		{
			pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
			break ;
		}
		usleep(500);
		pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
	}
	pthread_mutex_unlock(&philo->config->mutexs->died_all_ate_mutex);
}
