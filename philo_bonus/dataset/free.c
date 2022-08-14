/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 21:44:30 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 02:25:14 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	free_philos(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		free(config->philos[counter++]);
	free(config->philos);
	free(config->philo_pid_table);
	free(config->philo_status);
}

void	unlink_semaphore(void)
{
	sem_unlink("/s_forks");
	sem_unlink("/s_speak");
	sem_unlink("/s_begin");
	sem_unlink("/s_last_meal");
	sem_unlink("/s_nb_eat");
	sem_unlink("/s_take_fork");
	sem_unlink("/s_have_died");
}

void	destroy_semaphore(t_main *config)
{
	sem_close(config->s_forks);
	sem_close(config->s_speak);
	sem_close(config->s_begin);
	sem_close(config->s_last_meal);
	sem_close(config->s_nb_eat);
	sem_close(config->s_take_fork);
	sem_close(config->s_have_died);
	unlink_semaphore();
}

void	free_entry(t_main *config)
{
	free_philos(config);
	destroy_semaphore(config);
}
