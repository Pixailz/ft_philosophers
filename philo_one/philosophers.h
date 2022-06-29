/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:44 by brda-sil          #+#    #+#             */
/*   Updated: 2022/06/29 12:43:19 by brda-sil         ###   ########.fr       */
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
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				have_max_eat;
	int				max_eat;
	int				philo_died;
	int				philo_died_id;
	int				philo_all_ate;
	long long		start_timestamp;
	pthread_t		death;
	pthread_mutex_t	**forks;
	struct s_philo	**philos;
	struct s_mutexs	*mutexs;
}					t_main;

typedef struct s_mutexs
{
	pthread_mutex_t	print_action_mutex;
	pthread_mutex_t	last_meal_mutex;
	pthread_mutex_t	nb_eat_mutex;
	pthread_mutex_t	died_all_ate_mutex;
	pthread_mutex_t	all_ate_mutex;
}					t_mutexs;

typedef struct s_philo
{
	pthread_t	thread_id;
	t_main		*config;
	long long	last_meal;
	int			have_reached_max_eat;
	int			nb_eat;
	int			philo_id;
	int			l_fork_id;
	int			r_fork_id;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// dataset/ft_free.c
void			ft_destroy_mutex(t_main *config);
void			ft_free_entry(t_main *config);
void			ft_free_forks(t_main *config);
void			ft_free_philos(t_main *config);

// dataset/ft_init.c
int				ft_init(t_main *config);
int				ft_init_forks(t_main *config);
int				ft_init_mutex(t_main *config);
int				ft_init_philos(t_main *config);

// dataset/ft_parse.c
int				ft_parse(t_main *config, char **argv);
int				ft_parse_is_arg_too_big(t_main *config, char **argv);
int				ft_parse_is_good_int(char *to_test);
int				ft_parse_is_numeric(t_main *config, char **argv);

// debug/ft_debug.c
void			ft_debug_print_elapsed(long long elapsed);
void			ft_debug_print_initial(t_main *config);

// life/ft_death.c
void			ft_check_all_ate(int *nb_eat, t_main *config, int counter);
void			ft_check_last_meal(t_main *config, int counter);
void			*ft_death(void *void_config);
void			ft_death_2(t_main *config, int nb_eat);

// life/ft_eat.c
void			ft_eat(t_philo *philo);

// life/ft_sleep.c
void			ft_sleep_ng(t_philo *philo, long long begin, \
														long long time_to_wait);

// life/ft_solo.c
int				ft_solo_life_manager(t_main *config);
void			*ft_solo_live(void *void_philo);

// life/ft_world.c
void			ft_cycle_of_life(t_philo *philo);
int				ft_life_manager(t_main *config);
void			*ft_live(void *void_philo);
void			ft_say(t_main *config, int philo_id, char *action);

// philosophers.c
int				main(int argc, char **argv);

// time/ft_time.c
long long		ft_get_timestamp(void);

// utils/ft_atol.c
long			ft_atol(const char *ptr);

// utils/ft_error.c
int				ft_error_init(int return_code);
int				ft_error_life(int return_code);
int				ft_error_parse(int return_code);

// utils/ft_isnum.c
int				ft_isnum(const char *ptr);

/* ########################################################################## */

#endif
