/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:02:54 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 10:58:33 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	ft_get_timestamp(void)
{
	struct timeval	timestamp;

	gettimeofday(&timestamp, NULL);
	return (timestamp.tv_sec * 1000 + (timestamp.tv_usec / 1000));
}
