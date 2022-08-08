/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:43:20 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:06:46 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_config(t_main *config, char **argv)
{
	config->number_of_philosophers = ft_atol(argv[1]);
	config->time_to_die = ft_atol(argv[2]);
	config->time_to_eat = ft_atol(argv[3]);
	config->time_to_sleep = ft_atol(argv[4]);
	if (config->have_max_eat)
		config->max_eat = ft_atol(argv[5]);
	if (DEBUG)
		debug_print_initial_config(config);
	config->all_ate = 0;
	config->have_died = 0;
}

int	init_philos(t_main *config)
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
			return (2);
		config->philos[counter]->philo_id = counter + 1;
		config->philos[counter]->l_fork_id = counter;
		config->philos[counter]->r_fork_id = (counter + 1) % \
												config->number_of_philosophers;
		config->philos[counter]->config = config;
		config->philos[counter]->nb_eat = 0;
		config->philos[counter]->have_max_eaten = 0;
		counter++;
	}
	return (0);
}

int	init_forks(t_main *config)
{
	int	counter;

	config->forks = (pthread_mutex_t **)malloc(sizeof(pthread_mutex_t *) * \
												config->number_of_philosophers);
	if (!config->forks)
		return (3);
	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		config->forks[counter] = (pthread_mutex_t *)malloc \
													(sizeof(pthread_mutex_t));
		if (!config->forks[counter])
			return (4);
		if (pthread_mutex_init(config->forks[counter], NULL))
			return (5);
		counter++;
	}
	return (0);
}

int	init_mutex(t_main *config)
{
	if (pthread_mutex_init(&config->m_speak, NULL))
		return (6);
	if (pthread_mutex_init(&config->m_have_died, NULL))
		return (7);
	if (pthread_mutex_init(&config->m_all_ate, NULL))
		return (8);
	if (pthread_mutex_init(&config->m_last_meal, NULL))
		return (9);
	if (pthread_mutex_init(&config->m_nb_eat, NULL))
		return (10);
	return (0);
}

int	init_entry(t_main *config, char **argv)
{
	int	return_code;

	init_config(config, argv);
	return_code = init_philos(config);
	if (return_code)
		return (return_code);
	return_code = init_forks(config);
	if (return_code)
		return (return_code);
	return_code = init_mutex(config);
	if (return_code)
		return (return_code);
	return (0);
}
