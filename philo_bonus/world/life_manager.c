/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:02:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/11 04:03:11 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	cycle_of_life(t_philo *philo)
{
	while (VRAI)
	{
		eat(philo);
		say(philo, "is sleeping");
		sleep_ng(ft_get_timestamp_ms(), philo->config->time_to_sleep);
		say(philo, "is thinking");
	}
}

void	life(t_philo *philo)
{
	if (philo->philo_id % 2)
		usleep(500);
	cycle_of_life(philo);
}

int	life_manager(t_main *config)
{
	int		counter;
	t_stamp	begin;

	begin = ft_get_timestamp_ms();
	counter = 0;
	config->start_ts = begin;
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = begin;
		config->philo_pid_table[counter] = fork();
		if (config->philo_pid_table[counter] < 0)
			return (1);
		if (config->philo_pid_table[counter] == 0)
		{
			life(config->philos[counter]);
			break ;
		}
		counter++;
	}
	if (counter == config->number_of_philosophers)
	{
		// if (pthread_create(&config->death, NULL, death, config))
		// 	return (2);
		// if (pthread_join(config->death, NULL))
		// 	return (3);
	}
	return (0);
}
