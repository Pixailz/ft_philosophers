/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ng.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:09:26 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:48:13 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	sleep_ng(t_philo *philo, t_stamp begin, t_stamp time_to_wait)
{
	t_stamp	current_ts;
	t_main	*config;

	config = philo->config;
	ft_lock_both(config);
	while (!config->all_ate && !config->have_died)
	{
		ft_unlock_both(config);
		current_ts = ft_get_timestamp_ms();
		if (current_ts - begin >= time_to_wait)
		{
			ft_lock_both(config);
			break ;
		}
		usleep(SLEEP_TIME);
		ft_lock_both(config);
	}
	ft_unlock_both(config);
}
