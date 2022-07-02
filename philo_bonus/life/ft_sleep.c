/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 05:55:14 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/02 19:35:10 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_sleep_ng(t_philo *philo, long long begin, long long time_to_wait)
{
	long long	current_time;

	sem_wait(&philo->config->semaphores->died_all_ate_sem);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		sem_post(&philo->config->semaphores->died_all_ate_sem);
		current_time = ft_get_timestamp();
		if (current_time - begin >= time_to_wait)
		{
			sem_wait(&philo->config->semaphores->died_all_ate_sem);
			break ;
		}
		usleep(CHECK_TIME);
		sem_wait(&philo->config->semaphores->died_all_ate_sem);
	}
	sem_post(&philo->config->semaphores->died_all_ate_sem);
}
