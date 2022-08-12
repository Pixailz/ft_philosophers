/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 22:43:20 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/12 13:29:33 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	init_config(t_main *config, char **argv)
{
	int	counter;

	config->number_of_philosophers = ft_atol(argv[1]);
	config->time_to_die = ft_atol(argv[2]);
	config->time_to_eat = ft_atol(argv[3]);
	config->time_to_sleep = ft_atol(argv[4]);
	config->philo_has_died = 0;
	if (config->have_max_eat)
		config->max_eat = ft_atol(argv[5]);
	if (DEBUG)
		debug_print_initial_config(config);
	config->philo_pid_table = (pid_t *)malloc(sizeof(pid_t) * \
												config->number_of_philosophers);
	if (!config->philo_pid_table)
		return (1);
	config->philo_status = (int *)malloc(sizeof(int) * \
												config->number_of_philosophers);
	if (!config->philo_status)
		return (2);
	counter = 0;
	while (counter < config->number_of_philosophers)
		config->philo_status[counter++] = -1;
	return (0);
}

int	init_philos(t_main *config)
{
	int	counter;

	config->philos = (t_philo **)malloc(sizeof(t_philo *) * \
												config->number_of_philosophers);
	if (!config->philos)
		return (3);
	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter] = (t_philo *)malloc(sizeof(t_philo));
		if (!config->philos[counter])
			return (4);
		config->philos[counter]->philo_id = counter + 1;
		config->philos[counter]->config = config;
		config->philos[counter]->nb_eat = 0;
		config->philos[counter]->have_died = 0;
		config->philos[counter]->have_max_eaten = 0;
		counter++;
	}
	return (0);
}

int	init_semaphore(t_main *config)
{
	sem_unlink("/s_forks");
	sem_unlink("/s_speak");
	sem_unlink("/s_begin");
	config->s_forks = sem_open("/s_forks", O_CREAT, S_IRWXU, \
												config->number_of_philosophers);
	config->s_speak = sem_open("/s_speak", O_CREAT, S_IRWXU, 1);
	config->s_begin = sem_open("/s_begin", O_CREAT, S_IRWXU, 0);
	if (config->s_forks <= SEM_FAILED)
		return (5);
	if (config->s_speak <= SEM_FAILED)
		return (6);
	if (config->s_begin <= SEM_FAILED)
		return (7);
	return (0);
}

int	init_entry(t_main *config, char **argv)
{
	int	return_code;

	return_code = init_config(config, argv);
	if (return_code)
		return (return_code);
	return_code = init_philos(config);
	if (return_code)
		return (return_code);
	return_code = init_semaphore(config);
	if (return_code)
		return (return_code);
	return (0);
}
