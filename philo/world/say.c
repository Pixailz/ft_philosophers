/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   say.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 19:54:41 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/26 17:47:18 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	say(t_philo *philo, char *action)
{
	t_stamp	current_ts;

	ft_lock_both(philo->config);
	if (!philo->config->all_ate && !philo->config->have_died)
	{
		ft_unlock_both(philo->config);
		current_ts = ft_get_timestamp_ms() - philo->config->start_ts;
		pthread_mutex_lock(&philo->config->m_speak);
		if (DEBUG)
			debug_print_elapsed(current_ts);
		else
			printf("%lld", current_ts);
		printf(" %d ", philo->philo_id);
		printf("%s\n", action);
		pthread_mutex_unlock(&philo->config->m_speak);
		return ;
	}
	ft_unlock_both(philo->config);
}
