/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_ng.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/07 20:09:26 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 02:00:22 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	sleep_ng(t_philo *philo, t_stamp begin, t_stamp time_to_wait)
{
	t_stamp	current_ts;

	sem_wait(philo->config->s_have_died);
	while (!philo->have_died && !philo->have_max_eaten)
	{
		sem_post(philo->config->s_have_died);
		current_ts = ft_get_timestamp_ms();
		if (current_ts - begin >= time_to_wait)
			break ;
		usleep(SLEEP_TIME);
		sem_wait(philo->config->s_have_died);
	}
	sem_post(philo->config->s_have_died);
}
