/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:44 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/18 01:16:22 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ########################################################################## */
/* INCLUDE */
/* ####### */

# include "stdio.h"

/* ########################################################################## */

/* ########################################################################## */
/* CONFIG */
/* ###### */

# ifndef DEBUG
#  define DEBUG 0
# endif

# define INT_MAX 2147483647
# define INT_MIN -2147483648

/* ########################################################################## */

/* ########################################################################## */
/* STRUCT */
/* ###### */

typedef struct s_main
{
	int	numbers_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	have_max_eat;
	int	number_of_times_each_philosophers_must_eat;
}				t_main;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// init.c
void	init(t_main *config);

// parse.c
int		parse(t_main *config, char **argv);
int		parse_is_good_int(char *to_test);

// philosophers.c
int		main(int argc, char **argv);

// utils/ft_atol.c
long	ft_atol(const char *ptr);

// utils/ft_error.c
int		ft_error(char *msg);
int		ft_error_parse(int error_code);

/* ########################################################################## */

#endif
