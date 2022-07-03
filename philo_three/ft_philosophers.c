/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pilosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:57:29 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/28 19:56:03 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_main	config;
	int		return_code;

	if (argc != 5 && argc != 6)
		return (printf("Error\nWrong number of args\n"));
	config.have_max_eat = argc == 6;
	return_code = ft_parse(&config, argv);
	if (return_code)
		return (ft_error_parse(return_code));
	return_code = ft_init(&config);
	if (return_code)
		return (ft_error_init(return_code));
	if (config.number_of_philosophers == 1)
		return_code = ft_solo_life_manager(&config);
	else
		return_code = ft_life_manager(&config);
	if (return_code)
		return (ft_error_life(return_code));
	ft_free_entry(&config);
	return (0);
}
