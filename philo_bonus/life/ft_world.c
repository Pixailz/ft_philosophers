/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:48:59 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/02 19:50:14 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_say(t_main *config, int philo_id, char *action)
{
	long long	elapsed;

	if (!config->philo_died && !config->philo_all_ate)
	{
		elapsed = ft_get_timestamp() - config->start_timestamp;
		sem_wait(&config->semaphores->print_action_sem);
		if (DEBUG)
			ft_debug_print_elapsed(elapsed);
		else
			printf("%lld", elapsed);
		printf(" %d ", philo_id);
		printf("%s\n", action);
		sem_post(&config->semaphores->print_action_sem);
	}
}

void	ft_cycle_of_life(t_philo *philo)
{
	sem_wait(&philo->config->semaphores->died_all_ate_sem);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		sem_post(&philo->config->semaphores->died_all_ate_sem);
		ft_eat(philo);
		if (philo->config->philo_died || philo->config->philo_all_ate)
		{
			sem_wait(&philo->config->semaphores->died_all_ate_sem);
			break ;
		}
		ft_say(philo->config, philo->philo_id, "is sleeping");
		ft_sleep_ng(philo, ft_get_timestamp(), philo->config->time_to_sleep);
		ft_say(philo->config, philo->philo_id, "is thinking");
		sem_wait(&philo->config->semaphores->all_ate_sem);
		if (philo->have_reached_max_eat)
		{
			sem_post(&philo->config->semaphores->all_ate_sem);
			break ;
		}
		sem_post(&philo->config->semaphores->all_ate_sem);
		sem_wait(&philo->config->semaphores->died_all_ate_sem);
	}
	sem_post(&philo->config->semaphores->died_all_ate_sem);
}

pid_t	ft_live(t_philo *philo)
{
	sem_wait(&philo->config->semaphores->wait_for_all);
	sem_post(&philo->config->semaphores->wait_for_all);
	if (philo->philo_id % 2)
		usleep(500);
	if (DEBUG)
		printf("hello from philo[%d]\n", philo->philo_id);
	ft_cycle_of_life(philo);
	return (philo->pid_id);
}

int	ft_life_manager(t_main *config)
{
	int		counter;
	pid_t	current_pid;

	counter = 0;
	config->start_timestamp = ft_get_timestamp();
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = ft_get_timestamp();
		config->philos[counter]->pid_id = fork();
		if (config->philos[counter]->pid_id == -1)
			return (1);
		else if (config->philos[counter]->pid_id == 0)
			current_pid = ft_live(config->philos[counter]);
		else
			current_pid = 1;
		counter++;
	}
	if (current_pid)
		ft_death(config);
	else
		return (1);
	return (0);
}
