/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_death.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 04:50:13 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/03 17:13:52 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_check_all_ate(int *nb_eat, t_main *config, int counter)
{
	pthread_mutex_lock(&config->mutexs->nb_eat_mutex);
	if (config->philos[counter]->nb_eat >= config->max_eat)
	{
		config->philos[counter]->have_reached_max_eat = 1;
		(*nb_eat)++;
	}
	pthread_mutex_unlock(&config->mutexs->nb_eat_mutex);
}

void	ft_check_last_meal(t_main *config, int counter)
{
	long long	current_time;

	current_time = ft_get_timestamp();
	pthread_mutex_lock(&config->mutexs->last_meal_mutex);
	if (current_time - config->philos[counter]->last_meal >= \
															config->time_to_die)
	{
		ft_say(config, counter + 1, "died");
		pthread_mutex_lock(&config->mutexs->died_all_ate_mutex);
		config->philo_died = 1;
		pthread_mutex_unlock(&config->mutexs->died_all_ate_mutex);
	}
	pthread_mutex_unlock(&config->mutexs->last_meal_mutex);
}

void	*ft_death(void *void_config)
{
	int			counter;
	int			nb_eat;
	t_main		*config;

	config = (t_main *)void_config;
	while (!config->philo_died && !config->philo_all_ate)
	{
		nb_eat = 0;
		counter = 0;
		while (counter < config->number_of_philosophers)
		{
			ft_check_last_meal(config, counter);
			pthread_mutex_lock(&config->mutexs->all_ate_mutex);
			if (config->have_max_eat)
				ft_check_all_ate(&nb_eat, config, counter);
			pthread_mutex_unlock(&config->mutexs->all_ate_mutex);
			counter++;
		}
		ft_death_2(config, nb_eat);
	}
	return ((void *)0);
}

void	ft_death_2(t_main *config, int nb_eat)
{
	pthread_mutex_lock(&config->mutexs->died_all_ate_mutex);
	if (nb_eat == config->number_of_philosophers)
	{
		config->philo_all_ate = 1;
	}
	pthread_mutex_unlock(&config->mutexs->died_all_ate_mutex);
	usleep(CHECK_TIME);
}
