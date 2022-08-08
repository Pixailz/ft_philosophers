/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 01:19:51 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:20:10 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_lock_both(t_main *config)
{
	pthread_mutex_lock(&config->m_all_ate);
	pthread_mutex_lock(&config->m_have_died);
}

void	ft_unlock_both(t_main *config)
{
	pthread_mutex_unlock(&config->m_all_ate);
	pthread_mutex_unlock(&config->m_have_died);
}
