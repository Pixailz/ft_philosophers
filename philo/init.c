/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 01:09:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 03:21:35 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_init_mutex(t_main *config)
{

}


int	ft_init_forks(t_main *config)
{
	int	counter;

	counter = 0;
	config->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * \
												config->number_of_philosophers);
	if (!config->forks)
		return (1);
	while (counter < config->number_of_philosophers)
	{
		pthread_mutex_init(&config->forks[counter++], NULL);
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
		config->philos[counter]->philo_id = counter + 1;
		config->philos[counter]->l_fork_id = counter + 1;
		config->philos[counter]->r_fork_id = (counter + 1) % \
											config->number_of_philosophers;
		config->philos[counter]->config = config;
	}
	return (0);
}

int	ft_init(t_main *config)
{
	int	return_code;

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
