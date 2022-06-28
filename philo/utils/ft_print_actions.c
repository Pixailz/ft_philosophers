/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 20:05:26 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/28 20:08:49 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_print_actions(t_main *config, int philo_id, char *action)
{
	printf("%lld %d %s\n", ft_get_timestamp - config->timestamp, \
					philo_id, action);
}
