/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 04:50:13 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/04 14:36:24 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_kill_all_child(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		kill(config->philos[counter++]->pid_id, SIGTERM);
}

void	*ft_death(void *void_philo)
{
	t_philo		*philo;

	philo = (t_philo *)void_philo;
	while (VRAI)
	{
		sem_wait(philo->config->check_meal);
		if (ft_get_timestamp() - philo->last_meal >= philo->config->time_to_die)
		{
			ft_say(philo->config, philo->philo_id, "died");
			philo->config->philo_died = 1;
			sem_wait(philo->config->writing);
			ft_free_entry(philo->config);
			return (NULL);
		}
		sem_post(philo->config->check_meal);
		if (philo->config->philo_died)
			break ;
		sem_wait(philo->config->check_all_ate);
		if (philo->config->have_max_eat && \
										philo->nb_eat >= philo->config->max_eat)
		{
			sem_post(philo->config->check_all_ate);
			break ;
		}
		sem_post(philo->config->check_all_ate);
		usleep(CHECK_TIME);
	}
	return (NULL);
}
