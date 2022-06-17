/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 00:40:54 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 01:11:36 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_error_parse(int error_code)
{
	printf("Error\n");
	if (error_code == 1)
		printf("Wrong args: number_of_philosophers");
	if (error_code == 2)
		printf("Wrong args: time_to_die");
	if (error_code == 3)
		printf("Wrong args: time_to_eat");
	if (error_code == 4)
		printf("Wrong args: time_to_sleep");
	if (error_code == 5)
		printf("Wrong args: number_of_times_each_philosophers_must_eat");
}

int	ft_error(char *msg)
{
	printf("Error\n%s", msg);
	return (1);
}
