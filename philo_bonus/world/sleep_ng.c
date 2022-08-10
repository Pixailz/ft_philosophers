/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ng.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:09:26 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/10 20:01:25 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	sleep_ng(t_philo *philo, t_stamp begin, t_stamp time_to_wait)
{
	t_stamp	current_ts;
	t_main	*config;

	config = philo->config;
	while (VRAI)
	{
		current_ts = ft_get_timestamp_ms();
		if (current_ts - begin >= time_to_wait)
			break ;
		usleep(SLEEP_TIME);
	}
}
