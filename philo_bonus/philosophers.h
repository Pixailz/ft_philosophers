/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:11:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/10 03:00:41 by brda-sil         ###   ########.fr       */
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
#  define DEBUG 1
# endif

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define CHECK_TIME 1000
# define SLEEP_TIME 500

/* ########################################################################## */

/* ########################################################################## */
/* STRUCT */
/* ###### */

typedef long long	t_stamp;

typedef struct s_main
{
	int				have_max_eat;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_eat;
	int				have_died;
	int				all_ate;
	t_stamp			start_ts;
	pthread_t		death;
	pid_t			*philo_pid_table;
	struct s_philo	**philos;
}					t_main;

typedef struct s_philo
{
	int			philo_id;
	t_main		*config;
	int			l_fork_id;
	int			r_fork_id;
	int			nb_eat;
	int			have_max_eaten;
	t_stamp		last_meal;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// dataset/free.c
void		destroy_mutex(t_main *config);
void		free_entry(t_main *config);
void		free_forks(t_main *config);
void		free_philos(t_main *config);

// dataset/init.c
void		init_config(t_main *config, char **argv);
int			init_entry(t_main *config, char **argv);
int			init_forks(t_main *config);
int			init_mutex(t_main *config);
int			init_philos(t_main *config);

// dataset/parse.c
int			parse(t_main *config, char **argv);
int			parse_is_empty(t_main *config, char **argv);
int			parse_is_good_number(t_main *config, char **argv);
int			parse_is_numeric(t_main *config, char **argv);

// debug/debug.c
void		debug_print_elapsed(t_stamp current_ts);
void		debug_print_initial_config(t_main *config);

// philosophers.c
int			main(int argc, char **argv);

// utils/ft_atol.c
long int	ft_atol(const char *str);

// utils/ft_error.c
int			error_init(int return_code);
int			error_init2(int return_code);
int			error_life(int return_code);
int			error_parse(int ret_code);
int			ft_error(char *msg);

// utils/ft_get_timestamp_ms.c
t_stamp		ft_get_timestamp_ms(void);

// utils/ft_isnum.c
int			ft_isnumeric(const char *str);

// utils/ft_strlen.c
int			ft_strlen(const char *str);

// world/death.c
void		check_all_ate(t_philo *philo, int *nb_eat);
void		check_starving(t_philo *philo);
void		*death(void *void_config);

// world/eat.c
void		eat(t_philo *philo);
void		take_forks(t_philo *philo);

// world/life_manager.c
int			check_all_good(t_philo *philo);
void		cycle_of_life(t_philo *philo);
void		*life(void *void_philo);
int			life_manager(t_main *config);

// world/say.c
void		say(t_philo *philo, char *action);

// world/sleep_ng.c
void		sleep_ng(t_philo *philo, t_stamp begin, t_stamp time_to_wait);

// world/solitary_life_manager.c
void		*solo_life(void *void_philo);
int			solo_life_manager(t_main *config);

// world/utils.c
void		ft_lock_both(t_main *config);
void		ft_unlock_both(t_main *config);

/* ########################################################################## */

#endif
