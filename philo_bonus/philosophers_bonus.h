/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 18:11:43 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/10 20:00:35 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

/* ########################################################################## */
/* INCLUDE */
/* ####### */

/*
INT_MAX
INT_MIN
*/
# include <limits.h>
/*
pthread_t
pthread_create()
pthread_join()
*/
# include <pthread.h>
/*
malloc()
free()
*/
# include <stdlib.h>
/*
printf()
*/
# include <stdio.h>
/*
gettimeofday()
*/
# include <sys/time.h>
/*
usleep()
*/
# include <unistd.h>
/*
waitpid()
*/
# include <sys/wait.h>
/*
S_IRWXU
*/
# include <sys/stat.h>
/*
O_CREAT
*/
# include <fcntl.h>
/*
sem_open()
sem_unlink()
sem_close()
sem_post()
sem_wait()
*/
# include <semaphore.h>

/* ########################################################################## */

/* ########################################################################## */
/* CONFIG */
/* ###### */

# ifndef DEBUG
#  define DEBUG 1
# endif

# define VRAI 42
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
	t_stamp			start_ts;
	pthread_t		death;
	pid_t			*philo_pid_table;
	struct s_philo	**philos;
	sem_t			*s_forks;
	sem_t			*s_speak;
	sem_t			*s_begin;

}					t_main;

typedef struct s_philo
{
	int			philo_id;
	int			nb_eat;
	t_stamp		last_meal;
	int			still_here;
	t_main		*config;
}				t_philo;

/* ########################################################################## */

/* ########################################################################## */
/* FILES */
/* ##### */

// dataset/free.c
void		destroy_semaphore(t_main *config);
void		free_entry(t_main *config);
void		free_philos(t_main *config);

// dataset/init.c
int			init_config(t_main *config, char **argv);
int			init_entry(t_main *config, char **argv);
int			init_philos(t_main *config);
int			init_semaphore(t_main *config);

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
int			solo_life(t_philo *philo);
int			solo_life_manager(t_main *config);

// world/utils.c
void		ft_lock_both(t_main *config);
void		ft_unlock_both(t_main *config);

/* ########################################################################## */

#endif
