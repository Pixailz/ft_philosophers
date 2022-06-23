/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:44 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/20 15:13:14 by brda-sil         ###   ########.fr       */
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

/* ########################################################################## */

/* ########################################################################## */
/* STRUCT */
/* ###### */

typedef struct s_main
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_max_eat;
	int				number_of_times_each_philosophers_must_eat;
	struct timeval	begin;
	struct s_philo	**philos;
}				t_main;

typedef enum e_state {
	EATING,
	THINKING,
	SLEEPING
}			t_state;

typedef struct s_philo
{
	t_state	state;
	int		number;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// debug/debug.c
void		debug_print_initial(t_main *config);
void		print_elapsed(struct timeval *start);

// free.c
void		free_entry(t_main *config);
void		free_philo(t_main *config);

// init.c
void		init(t_main *config);

// parse.c
int			parse(t_main *config, char **argv);
int			parse_is_arg_too_big(t_main *config, char **argv);
int			parse_is_good_int(char *to_test);
int			parse_is_numeric(t_main *config, char **argv);

// philosophers.c
int			main(int argc, char **argv);

// time/time.c
float		get_elapsed(struct timeval *start);

// utils/ft_atol.c
long		ft_atol(const char *ptr);

// utils/ft_error.c
int			ft_error(char *msg);
int			ft_error_parse(int return_code);

// utils/ft_isnum.c
int			ft_isnum(const char *ptr);

/* ########################################################################## */

#endif
