/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wait.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 05:13:30 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/30 06:45:39 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*ft_wait_for_one_process(void *void_waiter)
{
	t_waiter	*waiter;

	waiter = (t_waiter *)void_waiter;
	waitpid(waiter->config->philos[waiter->id]->pid_id, NULL, 0);
	return (void_waiter);
}

void	ft_wait_for_all_process(t_main *config)
{
	int	counter;

	counter = 0;
	while (counter < config->number_of_philosophers)
	{
		pthread_create(&config->waiters[counter]->thread_id, NULL, \
						ft_wait_for_one_process, config->waiters[counter]);
		counter++;
	}
	counter = 0;
	printf("reach the barrier\n");
	while (counter < config->number_of_philosophers)
		pthread_join(config->waiters[counter++]->thread_id, NULL);
	printf("reach the barrier\n");
}
