/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:44 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 03:13:37 by brda-sil         ###   ########.fr       */
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
	long long		timestamp;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
	struct s_philo	**philos;
}				t_main;

typedef struct s_philo
{
	pthread_t	thread_id;
	t_main		*config;
	int			philo_id;
	int			l_fork_id;
	int			r_fork_id;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// debug/debug.c
void			ft_debug_print_initial(t_main *config);

// free.c
void			free_entry(t_main *config);
void			free_philo(t_main *config);

// init.c
int				ft_init(t_main *config);
int				ft_init_forks(t_main *config);
int				ft_init_philos(t_main *config);

// life/init.c
int				ft_life_begin(t_main *config);

// parse.c
int				ft_parse(t_main *config, char **argv);
int				ft_parse_is_arg_too_big(t_main *config, char **argv);
int				ft_parse_is_good_int(char *to_test);
int				ft_parse_is_numeric(t_main *config, char **argv);

// philosophers.c
int				main(int argc, char **argv);

// time/time.c
long long		ft_get_timestamp(void);

// utils/ft_atol.c
long			ft_atol(const char *ptr);

// utils/ft_error.c
int				ft_error(char *msg);
int				ft_error_init(int return_code);
int				ft_error_parse(int return_code);

// utils/ft_isnum.c
int				ft_isnum(const char *ptr);

// utils/ft_print_actions.c
void			ft_print_actions(t_main *config, int philo_id, char *action);

/* ########################################################################## */

#endif
