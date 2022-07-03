/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_world.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:48:59 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/03 17:13:18 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_say(t_main *config, int philo_id, char *action)
{
	long long	elapsed;

	if (!config->philo_died && !config->philo_all_ate)
	{
		elapsed = ft_get_timestamp() - config->start_timestamp;
		pthread_mutex_lock(&config->mutexs->print_action_mutex);
		if (DEBUG)
			ft_debug_print_elapsed(elapsed);
		else
			printf("%lld", elapsed);
		printf(" %d ", philo_id);
		printf("%s\n", action);
		pthread_mutex_unlock(&config->mutexs->print_action_mutex);
	}
}

void	ft_cycle_of_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
	while (!philo->config->philo_died && !philo->config->philo_all_ate)
	{
		pthread_mutex_unlock(&philo->config->mutexs->died_all_ate_mutex);
		ft_eat(philo);
		pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
		if (philo->config->philo_died || philo->config->philo_all_ate)
		{
			break ;
		}
		pthread_mutex_unlock(&philo->config->mutexs->died_all_ate_mutex);
		ft_say(philo->config, philo->philo_id, "is sleeping");
		ft_sleep_ng(philo, ft_get_timestamp(), philo->config->time_to_sleep);
		ft_say(philo->config, philo->philo_id, "is thinking");
		pthread_mutex_lock(&philo->config->mutexs->all_ate_mutex);
		if (philo->have_reached_max_eat)
		{
			pthread_mutex_unlock(&philo->config->mutexs->all_ate_mutex);
			pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->config->mutexs->all_ate_mutex);
		pthread_mutex_lock(&philo->config->mutexs->died_all_ate_mutex);
	}
	pthread_mutex_unlock(&philo->config->mutexs->died_all_ate_mutex);
}

void	*ft_live(void *void_philo)
{
	t_philo	*philo;

	philo = (t_philo *)void_philo;
	if (philo->philo_id % 2)
		usleep(500);
	ft_cycle_of_life(philo);
	return (void_philo);
}

int	ft_life_manager(t_main *config)
{
	int	counter;

	counter = 0;
	config->start_timestamp = ft_get_timestamp();
	while (counter < config->number_of_philosophers)
	{
		config->philos[counter]->last_meal = ft_get_timestamp();
		if (pthread_create(&config->philos[counter]->thread_id, NULL, \
									ft_live, config->philos[counter]))
			return (1);
		counter++;
	}
	if (pthread_create(&config->death, NULL, ft_death, config))
		return (1);
	if (pthread_join(config->death, NULL))
		return (2);
	counter = 0;
	while (counter < config->number_of_philosophers)
		if (pthread_join(config->philos[counter++]->thread_id, NULL))
			return (2);
	return (0);
}
