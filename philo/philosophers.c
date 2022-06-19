/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:57:29 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/19 17:39:29 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_main	config;
	int		return_code;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of args"));
	config.have_max_eat = argc == 6;
	return_code = parse(&config, argv);
	if (return_code)
		return (ft_error_parse(return_code));
	init(&config);
}
