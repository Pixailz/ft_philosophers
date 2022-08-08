/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:44:30 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:07:42 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philos(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->philos[counter++]);
	free(config->philos);
}

void	free_forks(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->forks[counter++]);
	free(config->forks);
}

void	destroy_mutex(t_main *config)
{
	pthread_mutex_destroy(&config->m_speak);
	pthread_mutex_destroy(&config->m_have_died);
	pthread_mutex_destroy(&config->m_all_ate);
}

void	free_entry(t_main *config)
{
	free_philos(config);
	free_forks(config);
	destroy_mutex(config);
}
