/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_solo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 09:24:32 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 05:09:21 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	ft_solo_live(t_philo *philo)
{
	sem_wait(philo->config->forks[0]);
	if (DEBUG)
		ft_say(philo->config, 1, "has taken a fork");
	else
		ft_say(philo->config, 1, "has taken a fork");
	ft_sleep_ng(philo, philo->last_meal, philo->config->time_to_die);
	sem_post(philo->config->forks[0]);
	ft_say(philo->config, 1, "died");
}

int	ft_solo_life_manager(t_main *config)
{
	config->start_timestamp = ft_get_timestamp();
	config->philos[0]->last_meal = ft_get_timestamp();
	config->philos[0]->pid_id = fork();
	if (config->philos[0]->pid_id == -1)
		return (1);
	else if (config->philos[0]->pid_id == 0)
		ft_solo_live(config->philos[0]);
	waitpid(config->philos[0]->pid_id, NULL, 0);
	return (0);
}
