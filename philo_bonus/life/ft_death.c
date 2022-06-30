/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 04:50:13 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 05:30:17 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_check_all_ate(int *nb_eat, t_main *config, int counter)
{
	sem_wait(&config->semaphores->nb_eat_semaphore);
	if (config->philos[counter]->nb_eat >= config->max_eat)
	{
		config->philos[counter]->have_reached_max_eat = 1;
		(*nb_eat)++;
	}
	sem_post(&config->semaphores->nb_eat_semaphore);
}

void	ft_check_last_meal(t_main *config, int counter)
{
	long long	current_time;

	current_time = ft_get_timestamp();
	sem_wait(&config->semaphores->last_meal_semaphore);
	if (current_time - config->philos[counter]->last_meal >= \
															config->time_to_die)
	{
		ft_say(config, counter + 1, "died");
		sem_wait(&config->semaphores->died_all_ate_semaphore);
		config->philo_died = 1;
		sem_post(&config->semaphores->died_all_ate_semaphore);
	}
	sem_post(&config->semaphores->last_meal_semaphore);
}

void	ft_death(t_main *config)
{
	int			counter;
	int			nb_eat;

	while (!config->philo_died && !config->philo_all_ate)
	{
		nb_eat = 0;
		counter = 0;
		while (counter < config->number_of_philosophers)
		{
			ft_check_last_meal(config, counter);
			sem_wait(&config->semaphores->all_ate_semaphore);
			if (config->have_max_eat)
				ft_check_all_ate(&nb_eat, config, counter);
			sem_post(&config->semaphores->all_ate_semaphore);
			counter++;
		}
		if (nb_eat == config->number_of_philosophers)
			config->philo_all_ate = 1;
		usleep(CHECK_TIME);
	}
}
