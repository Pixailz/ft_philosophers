/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:54:41 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/13 10:47:01 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	say(t_philo *philo, char *action)
{
	t_stamp	current_ts;

	if (!philo->have_died && !philo->have_max_eaten)
	{
		current_ts = ft_get_timestamp_ms() - philo->config->start_ts;
		sem_wait(philo->config->s_speak);
		if (DEBUG)
			debug_print_elapsed(current_ts);
		else
			printf("%lld", current_ts);
		printf(" %d ", philo->philo_id);
		printf("%s\n", action);
		sem_post(philo->config->s_speak);
	}
}
