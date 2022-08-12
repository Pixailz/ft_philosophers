/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:02:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/12 03:11:03 by brda-sil         ###   ########.fr       */
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

int	god_manager(t_main *config)
{
	if (pthread_create(&config->god, NULL, god, config))
		return (2);
	if (pthread_join(config->god, NULL))
		return (3);
	return (0);
}

int	life_manager(t_main *config)
{
	int		counter;
	t_stamp	begin;
	int		return_code;

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
		return_code = god_manager(config);
	return (return_code);
}
