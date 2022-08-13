/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 22:02:53 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/13 12:48:32 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	cycle_of_life(t_philo *philo)
{
	sem_wait(philo->config->s_begin);
	while (!philo->have_died && !philo->have_max_eaten)
	{
		eat(philo);
		say(philo, "is sleeping");
		sleep_ng(philo, ft_get_timestamp_ms(), philo->config->time_to_sleep);
		say(philo, "is thinking");
	}
	if (philo->have_max_eaten)
		exit(2);
	if (philo->have_died)
		exit(1);
}

void	life(t_philo *philo)
{
	if (philo->philo_id % 2)
		usleep(500);
	if (pthread_create(&philo->death, NULL, death, philo))
		exit(4);
	cycle_of_life(philo);
	if (pthread_join(philo->death, NULL))
		exit(5);
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
	counter = -1;
	config->start_ts = begin;
	while (++counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = begin;
		config->philo_pid_table[counter] = fork();
		if (config->philo_pid_table[counter] < 0)
			return (1);
		if (config->philo_pid_table[counter] == 0)
			break ;
	}
	if (counter == config->number_of_philosophers)
		return_code = god_manager(config);
	else
		life(config->philos[counter]);
	return (return_code);
}
