/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:11:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/02 22:53:14 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ########################################################################## */
/* INCLUDE */
/* ####### */

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <pthread.h>

/* ########################################################################## */

/* ########################################################################## */
/* CONFIG */
/* ###### */

# ifndef DEBUG
#  define DEBUG 1
# endif

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define CHECK_TIME 1000

/* ########################################################################## */

/* ########################################################################## */
/* STRUCT */
/* ###### */

typedef struct s_main
{
	int	have_max_eat;
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	max_eat;
}				t_main;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// dataset/init.c
void		init_config(t_main *config, char **argv);
int			init_entry(t_main *config, char **argv);

// dataset/parse.c
int			parse(t_main *config, char **argv);
int			parse_is_empty(t_main *config, char **argv);
int			parse_is_good_number(t_main *config, char **argv);
int			parse_is_numeric(t_main *config, char **argv);

// debug/debug.c
void		debug_print_initial_config(t_main *config);

// philosophers.c
int			main(int argc, char **argv);

// utils/ft_atol.c
long int	ft_atol(const char *str);

// utils/ft_error.c
int			ft_error(char *msg);
int			ft_error_init(int return_code);
int			ft_error_parse(int ret_code);

// utils/ft_isnum.c
int			ft_isnumeric(const char *str);

// utils/ft_strlen.c
int			ft_strlen(const char *str);

/* ########################################################################## */

#endif
