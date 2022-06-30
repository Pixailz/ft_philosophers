/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:48:59 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 06:40:20 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_say(t_main *config, int philo_id, char *action)
{
	long long	elapsed;

	if (!config->philo_died && !config->philo_all_ate)
	{
		elapsed = ft_get_timestamp() - config->start_timestamp;
		sem_wait(&config->semaphores->print_action_semaphore);
		if (DEBUG)
			ft_debug_print_elapsed(elapsed);
		else
			printf("%lld", elapsed);
		printf(" %d ", philo_id);
		printf("%s\n", action);
		sem_post(&config->semaphores->print_action_semaphore);
	}
}

void	ft_cycle_of_life(t_philo *philo)
{
	sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		sem_post(&philo->config->semaphores->died_all_ate_semaphore);
		ft_eat(philo);
		if (philo->config->philo_died || philo->config->philo_all_ate)
		{
			sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
			break ;
		}
		ft_say(philo->config, philo->philo_id, "is sleeping");
		ft_sleep_ng(philo, ft_get_timestamp(), philo->config->time_to_sleep);
		ft_say(philo->config, philo->philo_id, "is thinking");
		sem_wait(&philo->config->semaphores->all_ate_semaphore);
		if (philo->have_reached_max_eat)
		{
			sem_post(&philo->config->semaphores->all_ate_semaphore);
			break ;
		}
		sem_post(&philo->config->semaphores->all_ate_semaphore);
		sem_wait(&philo->config->semaphores->died_all_ate_semaphore);
	}
	sem_post(&philo->config->semaphores->died_all_ate_semaphore);
}

void	ft_live(t_philo *philo)
{
	if (philo->philo_id % 2)
		usleep(500);
	printf("hello from philo[%d]\n", philo->philo_id);
	ft_cycle_of_life(philo);
}

int	ft_life_manager(t_main *config)
{
	int	counter;

	counter = 0;
	config->start_timestamp = ft_get_timestamp();
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = ft_get_timestamp();
		config->philos[counter]->pid_id = fork();
		if (config->philos[counter]->pid_id == -1)
			return (1);
		else if (config->philos[counter]->pid_id == 0)
			ft_live(config->philos[counter]);
		counter++;
	}
	ft_death(config);
	ft_wait_for_all_process(config);
	return (0);
}
