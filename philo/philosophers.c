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

#include "philosophers.h"

int	main(int argc, char **argv)
{
	t_main	config;
	int		return_code;

	if (argc != 5 && argc != 6)
		return (ft_error("Wrong number of args"));
	config.have_max_eat = argc == 6;
	return_code = ft_parse(&config, argv);
	if (return_code)
		return (ft_error_parse(return_code));
	return_code = ft_init(&config);
	if (return_code)
		return (ft_error_init(return_code));
	free_entry(&config);
}

/*
# include <time.h>
//void	*roll_dice(void *test)
{
	int	value;
	int	*result;

	value = (rand() % 6) + 1;
	result = (int *)malloc(sizeof(int));
	*result = value;
	test = 0;
	return ((void *)(result));
}

//int	main(void)
{
	pthread_t	t1;
	int			*result;

	srand(time(NULL));
	if (pthread_create(&t1, NULL, &roll_dice, NULL))
		return (1);
	if (pthread_join(t1, (void **)&result))
		return (1);
	printf("result: %d\n", *result);
} */
