/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:55 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 11:52:24 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_free_philos(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->philos[counter++]);
	free(config->philos);
}

void	ft_free_forks(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->forks[counter++]);
	free(config->forks);
}

void	ft_destroy_mutex(t_main *config)
{
	pthread_mutex_destroy(&config->mutexs->print_action_mutex);
	pthread_mutex_destroy(&config->mutexs->last_meal_mutex);
	pthread_mutex_destroy(&config->mutexs->nb_eat_mutex);
	pthread_mutex_destroy(&config->mutexs->died_all_ate_mutex);
	pthread_mutex_destroy(&config->mutexs->all_ate_mutex);
	free(config->mutexs);
}

void	ft_free_entry(t_main *config)
{
	ft_free_philos(config);
	ft_free_forks(config);
	ft_destroy_mutex(config);
}
