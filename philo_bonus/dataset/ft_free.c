/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:55 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 06:31:37 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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

void	ft_destroy_semaphore(t_main *config)
{
	sem_close(&config->semaphores->print_action_semaphore);
	sem_close(&config->semaphores->last_meal_semaphore);
	sem_close(&config->semaphores->nb_eat_semaphore);
	sem_close(&config->semaphores->died_all_ate_semaphore);
	sem_close(&config->semaphores->all_ate_semaphore);
	free(config->semaphores);
}

void	ft_free_waiters(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->waiters[counter++]);
	free(config->waiters);
}

void	ft_free_entry(t_main *config)
{
	ft_free_philos(config);
	ft_free_forks(config);
	ft_destroy_semaphore(config);
	ft_free_waiters(config);
}
