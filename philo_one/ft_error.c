/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:40:54 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 06:42:24 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error_life(int return_code)
{
	printf("Error\n");
	if (return_code == 1)
		printf("failed to create thread\n");
	if (return_code == 2)
		printf("failed to join thread\n");
	return (return_code);
}

int	ft_error_init(int return_code)
{
	printf("Error\n");
	if (return_code == 1)
		printf("malloc\n");
	if (return_code == 2)
		printf("init mutex\n");
	return (return_code);
}

int	ft_error_parse(int return_code)
{
	printf("Error\n");
	if (return_code <= 5)
		printf("Args must be numeric: ");
	if (return_code > 5 && return_code <= 10)
		printf("Number too big/small: ");
	if (return_code == 1 || return_code == 6)
		printf("number_of_philosophers\n");
	if (return_code == 2 || return_code == 7)
		printf("time_to_die\n");
	if (return_code == 3 || return_code == 8)
		printf("time_to_eat\n");
	if (return_code == 4 || return_code == 9)
		printf("time_to_sleep\n");
	if (return_code == 5 || return_code == 10)
		printf("max_eat\n");
	return (return_code);
}
