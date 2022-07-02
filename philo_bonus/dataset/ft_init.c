/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:09:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/02 19:37:30 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_init_semaphore(t_main *config)
{
	config->semaphores = (t_semaphores *)malloc(sizeof(t_semaphores));
	if (!config->semaphores)
		return (1);
	if (sem_init(&config->semaphores->print_action_sem, 1, 1))
		return (2);
	if (sem_init(&config->semaphores->last_meal_sem, 1, 1))
		return (2);
	if (sem_init(&config->semaphores->nb_eat_sem, 1, 1))
		return (2);
	if (sem_init(&config->semaphores->died_all_ate_sem, 1, 1))
		return (2);
	if (sem_init(&config->semaphores->all_ate_sem, 1, 1))
		return (2);
	if (sem_init(&config->semaphores->wait_for_all, 1, \
											config->number_of_philosophers + 1))
		return (2);
	return (0);
}

int	ft_init_forks(t_main *config)
{
	int	counter;

	counter = 0;
	config->forks = (sem_t **)malloc(sizeof(sem_t *) * \
												config->number_of_philosophers);
	if (!config->forks)
		return (1);
	while (counter < config->number_of_philosophers)
	{
		config->forks[counter] = (sem_t *)malloc(sizeof(sem_t));
		if (!config->forks[counter])
			return (1);
		if (sem_init(config->forks[counter], 1, 1))
			return (2);
		counter++;
	}
	return (0);
}

int	ft_init_philos(t_main *config)
{
	int	counter;

	config->philos = (t_philo **)malloc(sizeof(t_philo *) * \
												config->number_of_philosophers);
	if (!config->philos)
		return (1);
	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter] = (t_philo *)malloc(sizeof(t_philo));
		if (!config->philos[counter])
			return (1);
		config->philos[counter]->have_reached_max_eat = 0;
		config->philos[counter]->philo_id = counter + 1;
		config->philos[counter++]->config = config;
	}
	return (0);
}

int	ft_init(t_main *config)
{
	int	return_code;

	config->philo_died = 0;
	config->philo_all_ate = 0;
	config->philo_died_id = -1;
	return_code = ft_init_philos(config);
	if (return_code)
		return (return_code);
	return_code = ft_init_forks(config);
	if (return_code)
		return (return_code);
	return_code = ft_init_semaphore(config);
	if (return_code)
		return (return_code);
	return (0);
}
