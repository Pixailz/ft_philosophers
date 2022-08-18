/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:14:39 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/18 22:15:46 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	ft_putstr_strderr(const char *msg)
{
	char	*msg_ptr;

	msg_ptr = (char *)msg;
	while (*msg_ptr)
		msg_ptr++;
	return (write(2, msg, msg_ptr - msg));
}

int	error_parse(int ret_code)
{
	ft_putstr_strderr("Error: ");
	if (ret_code == 1 || ret_code == 6 || ret_code == 11 || ret_code == 16)
		ft_putstr_strderr("(number of philosophers)\n");
	if (ret_code == 2 || ret_code == 7 || ret_code == 12 || ret_code == 17)
		ft_putstr_strderr("(time to die)\n");
	if (ret_code == 3 || ret_code == 8 || ret_code == 13 || ret_code == 18)
		ft_putstr_strderr("(time to eat)\n");
	if (ret_code == 4 || ret_code == 9 || ret_code == 14 || ret_code == 19)
		ft_putstr_strderr("(time to sleep)\n");
	if (ret_code == 5 || ret_code == 10 || ret_code == 15 || ret_code == 20)
		ft_putstr_strderr("(max eat)\n");
	if (ret_code <= 5)
		ft_putstr_strderr("String cannot be empty\n");
	if (ret_code > 5 && ret_code <= 10)
		ft_putstr_strderr("String is not numeric\n");
	if (ret_code > 10 && ret_code <= 15)
		ft_putstr_strderr("String can't be negative\n");
	if (ret_code > 15 && ret_code <= 20)
		ft_putstr_strderr("String is too big\n");
	return (ret_code);
}

int	error_init(int return_code)
{
	ft_putstr_strderr("Error: ");
	if (return_code == 1)
		ft_putstr_strderr("malloc (*philo_pid_table)\n");
	if (return_code == 2)
		ft_putstr_strderr("malloc (*philo_status)\n");
	if (return_code == 3)
		ft_putstr_strderr("malloc (**philos)\n");
	if (return_code == 4)
		ft_putstr_strderr("malloc (*philo)\n");
	if (return_code == 5)
		ft_putstr_strderr("init semaphore (s_forks)\n");
	if (return_code == 6)
		ft_putstr_strderr("init semaphore (s_speak)\n");
	if (return_code == 7)
		ft_putstr_strderr("init semaphore (s_begin)\n");
	if (return_code == 8)
		ft_putstr_strderr("init semaphore (s_last_meal)\n");
	if (return_code == 9)
		ft_putstr_strderr("init semaphore (s_nb_eat)\n");
	if (return_code == 10)
		ft_putstr_strderr("init semaphore (s_take_fork)\n");
	if (return_code == 11)
		ft_putstr_strderr("init semaphore (s_have_died)\n");
	return (return_code);
}

int	error_life(int return_code)
{
	if (return_code == 1)
		ft_putstr_strderr("Error: (create thread)");
	if (return_code == 2)
		ft_putstr_strderr("Error: (joining thread)");
	return (return_code);
}
