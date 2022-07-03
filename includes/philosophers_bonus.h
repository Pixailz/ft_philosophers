/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 23:56:44 by brda-sil          #+#    #+#             */
/*   Updated: 2022/07/03 11:56:21 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/* ########################################################################## */
/* INCLUDE */
/* ####### */

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>

/* ########################################################################## */

/* ########################################################################## */
/* CONFIG */
/* ###### */

# ifndef DEBUG
#  define DEBUG 0
# endif

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define CHECK_TIME 500

/* ########################################################################## */

/* ########################################################################## */
/* STRUCT */
/* ###### */

typedef struct s_main
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					have_max_eat;
	int					max_eat;
	int					philo_died;
	int					philo_died_id;
	int					philo_all_ate;
	long long			start_timestamp;
	struct s_philo		**philos;
	sem_t				*forks;
	sem_t				*writing;
	sem_t				*check_meal;
}					t_main;

typedef struct s_philo
{
	pthread_t	ft_death;
	pid_t		pid_id;
	t_main		*config;
	long long	last_meal;
	int			have_reached_max_eat;
	int			nb_eat;
	int			philo_id;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// dataset/ft_free.c
void			ft_destroy_semaphore(t_main *config);
void			ft_free_entry(t_main *config);
void			ft_free_philos(t_main *config);

// dataset/ft_init.c
int				ft_init(t_main *config);
int				ft_init_philos(t_main *config);
int				ft_init_semaphore(t_main *config);

// dataset/ft_parse.c
int				ft_parse(t_main *config, char **argv);
int				ft_parse_is_arg_too_big(t_main *config, char **argv);
int				ft_parse_is_good_int(char *to_test);
int				ft_parse_is_numeric(t_main *config, char **argv);

// debug/ft_debug.c
void			ft_debug_print_elapsed(long long elapsed);
void			ft_debug_print_initial(t_main *config);

// life/ft_death.c
void			*ft_death(void *void_philo);
void			ft_kill_all_child(t_main *config);

// life/ft_eat.c
void			ft_eat(t_philo *philo);

// life/ft_sleep.c
void			ft_sleep_ng(t_philo *philo, long long begin, \
														long long time_to_wait);

// life/ft_solo.c
int				ft_solo_life_manager(t_main *config);
void			ft_solo_live(t_philo *philo);

// life/ft_world.c
void			ft_cycle_of_life(t_philo *philo);
int				ft_life_manager(t_main *config);
pid_t			ft_live(t_philo *philo);
void			ft_say(t_main *config, int philo_id, char *action);
void			ft_waiter(t_main *config);

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
