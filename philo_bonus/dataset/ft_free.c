/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 15:13:55 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/04 14:03:13 by brda-sil         ###   ########.fr       */
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

void	ft_destroy_semaphore(t_main *config)
{
	sem_close(config->check_meal);
	sem_close(config->check_all_ate);
	sem_close(config->writing);
	sem_close(config->forks);
	sem_unlink("/check_meal");
	sem_unlink("/check_all_ate");
	sem_unlink("/philo_writing");
	sem_unlink("/philo_forks");
}

void	ft_free_entry(t_main *config)
{
	ft_free_philos(config);
	ft_destroy_semaphore(config);
}
