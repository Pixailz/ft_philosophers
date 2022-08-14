/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   god_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 03:13:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 14:52:30 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	kill_all(t_main *config)
{
	int	counter;

	counter = 0;
	// say(config->philos[philo_id], "has died");
	//sem_wait(config->s_speak);
	while (counter < config->number_of_philosophers)
		kill(config->philo_pid_table[counter++], 9);
	if (DEBUG)
		printf("GOD killed all philos\n");
}

int	check_all_ate(t_main *config, int philo_id)
{
	int	counter;
	int	nb_eat;

	counter = 0;
	nb_eat = 0;
	config->philos[philo_id]->have_max_eaten = 1;
	while (counter < config->number_of_philosophers)
		if (config->philos[counter++]->have_max_eaten)
			nb_eat++;
	return (nb_eat == config->number_of_philosophers);
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
									&config->philo_status[counter], WNOHANG);
			// printf("philo[%d] has exited\n", counter + 1);
			if (WIFEXITED(config->philo_status[counter]))
			{
				if (config->philo_status[counter] >> 8 == 1)
				{
					kill_all(config);
					return (1);
				}
				else if (config->philo_status[counter] >> 8 == 2)
					if (check_all_ate(config, counter))
						return (2);
			}
		}
		counter++;
	}
	return (0);
}

void	start_life(t_main *config)
{
	int		counter;

	counter = 0;
	while (counter++ < config->number_of_philosophers)
		sem_post(config->s_begin);
}

void	*god(void *void_config)
{
	t_main	*config;
	int		return_code;

	config = (t_main *)void_config;
	start_life(config);
	while (VRAI)
	{
		return_code = check_pid_status(config);
		if (return_code != 0)
			break ;
	}
	return (void_config);
}
