/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:55:14 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 05:20:10 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sleep_ng(t_philo *philo, long long begin, long long time_to_wait)
{
	long long	current_time;

	sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		sem_post(&philo->config->semaphores->died_all_ate_semaphore);
		current_time = ft_get_timestamp();
		if (current_time - begin >= time_to_wait)
		{
			sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
			break ;
		}
		usleep(CHECK_TIME);
		sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
	}
	sem_post(&philo->config->semaphores->died_all_ate_semaphore);
}
