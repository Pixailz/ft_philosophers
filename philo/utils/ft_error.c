/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:14:39 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/08 01:07:32 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_parse(int ret_code)
{
	printf("Error: ");
	if (ret_code == 1 || ret_code == 6 || ret_code == 11 || ret_code == 16)
		printf("(number of philosophers)\n");
	if (ret_code == 2 || ret_code == 7 || ret_code == 12 || ret_code == 17)
		printf("(time to die)\n");
	if (ret_code == 3 || ret_code == 8 || ret_code == 13 || ret_code == 18)
		printf("(time to eat)\n");
	if (ret_code == 4 || ret_code == 9 || ret_code == 14 || ret_code == 19)
		printf("(time to sleep)\n");
	if (ret_code == 5 || ret_code == 10 || ret_code == 15 || ret_code == 20)
		printf("(max eat)\n");
	if (ret_code <= 5)
		printf("String cannot be empty\n");
	if (ret_code > 5 && ret_code <= 10)
		printf("String is not numeric\n");
	if (ret_code > 10 && ret_code <= 15)
		printf("String can't be negative\n");
	if (ret_code > 15 && ret_code <= 20)
		printf("String is too big\n");
	return (ret_code);
}

int	error_init2(int return_code)
{
	if (return_code == 11)
		printf("m_nb_eat\n");
	return (return_code);
}

int	error_init(int return_code)
{
	printf("Error: ");
	if (return_code >= 1 && return_code <= 4)
		printf("malloc");
	else if (return_code >= 5)
		printf("init mutex");
	if (return_code == 1)
		printf("(**philos)\n");
	if (return_code == 2)
		printf("(*philo)\n");
	if (return_code == 3)
		printf("(**forks)\n");
	if (return_code == 4 || return_code == 5)
		printf("(*fork)\n");
	if (return_code == 6)
		printf("(m_speak)\n");
	if (return_code == 7)
		printf("(m_have_died)\n");
	if (return_code == 8)
		printf("(m_last_meal)\n");
	if (return_code == 10)
		printf("(m_nb_eat)\n");
	return (error_init2(return_code));
}

int	error_life(int return_code)
{
	if (return_code == 1)
		printf("Error: (create thread)");
	if (return_code == 2)
		printf("Error: (joining thread)");
	return (return_code);
}

int	ft_error(char *msg)
{
	if (msg)
		printf("Error: %s\n", msg);
	else
		printf("Error\n");
	return (-1);
}
