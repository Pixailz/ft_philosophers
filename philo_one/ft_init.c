/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:09:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 11:51:52 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_main *config)
{
	config->mutexs = (t_mutexs *)malloc(sizeof(t_mutexs));
	if (!config->mutexs)
		return (1);
	if (pthread_mutex_init(&config->mutexs->print_action_mutex, NULL))
		return (2);
	if (pthread_mutex_init(&config->mutexs->last_meal_mutex, NULL))
		return (2);
	if (pthread_mutex_init(&config->mutexs->nb_eat_mutex, NULL))
		return (2);
	if (pthread_mutex_init(&config->mutexs->died_all_ate_mutex, NULL))
		return (2);
	if (pthread_mutex_init(&config->mutexs->all_ate_mutex, NULL))
		return (2);
	return (0);
}

int	ft_init_forks(t_main *config)
{
	int	counter;

	counter = 0;
	config->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * \
												config->number_of_philosophers);
	if (!config->forks)
		return (1);
	while (counter < config->number_of_philosophers)
	{
		config->forks[counter] = \
							(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
		if (!config->forks[counter])
			return (1);
		if (pthread_mutex_init(config->forks[counter], NULL))
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
		config->philos[counter]->l_fork_id = counter;
		config->philos[counter]->r_fork_id = (counter + 1) % \
												config->number_of_philosophers;
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
	return_code = ft_init_mutex(config);
	if (return_code)
		return (return_code);
	return (0);
}
