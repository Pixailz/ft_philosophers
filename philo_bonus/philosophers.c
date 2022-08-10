/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:13:03 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/10 20:01:25 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	main(int argc, char **argv)
{
	t_main	config;
	int		return_code;

	if (argc != 5 && argc != 6)
		return (printf("Error: Not enought args\n"));
	config.have_max_eat = argc == 6;
	return_code = parse(&config, argv);
	if (return_code)
		return (error_parse(return_code));
	return_code = init_entry(&config, argv);
	if (return_code)
		return (error_init(return_code));
	if (config.number_of_philosophers == 1)
		return_code = solo_life_manager(&config);
	else
		return_code = life_manager(&config);
	if (return_code)
		return (error_life(return_code));
	free_entry(&config);
	return (0);
}
