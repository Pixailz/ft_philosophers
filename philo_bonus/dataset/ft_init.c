/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:09:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/03 03:04:22 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_init_semaphore(t_main *config)
{
	sem_unlink("/philo_check_meal");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_forks");
	config->check_meal = sem_open("/philo_check_meal", O_CREAT, S_IRWXU, 1);
	config->writing = sem_open("/philo_writing", O_CREAT, S_IRWXU, 1);
	config->forks = sem_open("/philo_forks", O_CREAT, S_IRWXU, \
												config->number_of_philosophers);
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
		config->philos[counter]->nb_eat = 0;
		config->philos[counter]->last_meal = 0;
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
	return_code = ft_init_semaphore(config);
	if (return_code)
		return (return_code);
	return (0);
}
