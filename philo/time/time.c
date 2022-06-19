/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 22:02:54 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/19 22:44:25 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

float	get_elapsed(struct timeval *start, struct timeval *end)
{
	float	sec;
	float	usec;

	sec = (float)(end->tv_sec - start->tv_sec);
	usec = (int)((float)end->tv_usec - (float)start->tv_usec) / 1000;
	usec = (float)(usec / 1000);
	return (sec + usec);
}
