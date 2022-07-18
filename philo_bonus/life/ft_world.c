/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:48:59 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/04 14:37:32 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_say(t_main *config, int philo_id, char *action)
{
	long long	elapsed;

	sem_wait(config->writing);
	if (!config->philo_died && !config->philo_all_ate)
	{
		elapsed = ft_get_timestamp() - config->start_timestamp;
		if (DEBUG)
			ft_debug_print_elapsed(elapsed);
		else
			printf("%lld", elapsed);
		printf(" %d ", philo_id);
		printf("%s\n", action);
	}
	sem_post(config->writing);
}

void	ft_cycle_of_life(t_philo *philo)
{
	while (!philo->config->philo_died)
	{
		ft_eat(philo);
		if (philo->config->have_max_eat && \
										philo->nb_eat >= philo->config->max_eat)
			break ;
		ft_say(philo->config, philo->philo_id, "is sleeping");
		ft_sleep_ng(philo, ft_get_timestamp(), philo->config->time_to_sleep);
		ft_say(philo->config, philo->philo_id, "is thinking");
	}
}

pid_t	ft_live(t_philo *philo)
{
	philo->last_meal = ft_get_timestamp();
	pthread_create(&philo->ft_death, NULL, ft_death, (void *)philo);
	if (philo->philo_id % 2)
		usleep(500);
	ft_cycle_of_life(philo);
	pthread_join(philo->ft_death, NULL);
	if (philo->config->philo_died)
		exit(1);
	exit(0);
}

void	ft_waiter(t_main *config)
{
	int	counter;
	int	result;

	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		waitpid(-1, &result, 0);
		if (result != 0)
		{
			ft_kill_all_child(config);
			break ;
		}
		counter++;
	}
}

int	ft_life_manager(t_main *config)
{
	int		counter;

	counter = 0;
	config->start_timestamp = ft_get_timestamp();
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->pid_id = fork();
		if (config->philos[counter]->pid_id == -1)
			return (1);
		else if (config->philos[counter]->pid_id == 0)
			ft_live(config->philos[counter]);
		counter++;
	}
	if (counter == config->number_of_philosophers)
		ft_waiter(config);
	return (0);
}
