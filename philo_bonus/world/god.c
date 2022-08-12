/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 03:13:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/12 13:58:31 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	kill_all(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
		kill(config->philo_pid_table[counter], 9);
}

int	check_pid_status(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		if (config->philo_status[counter] == -1)
		{
			waitpid(config->philo_pid_table[counter], \
										config->philo_status[counter], WNOHANG);
			if (WIFEXITED(config->philo_status[counter]))
			{
				config->philo_status[counter] = \
									WEXITSTATUS(config->philo_status[counter]);
				if ()
				say(config->philos[counter], "had died");
				kill_all(config);
				config->philo_has_died = 1;
				return (1);
			}
		}
		counter++;
	}
	return (0);
}

void	*god(void *void_config)
{
	t_main	*config;

	config = (t_main *)config;
	while (config->philo_has_died)
	{
		if (check_status(config))
			break ;

	}
	return (void_config);
}
