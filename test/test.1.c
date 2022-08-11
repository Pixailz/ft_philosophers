/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:45:28 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/11 03:36:33 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <signal.h>

#define TIME_TO_WAIT 200000
#define CHECKTIME 500

long int	ft_atol(char *str);
long long	ft_get_timestamp_ms(void);

sem_t		*g_s_begin;
sem_t		*g_s_speak;
sem_t		*g_s_eating;

long long	g_begin;

void	say(char *msg, int id)
{
	long long	elapsed;

	elapsed = ft_get_timestamp_ms() - g_begin;
	sem_wait(g_s_speak);
	if (!id)
		printf("(%lld)\t[main] %s\n", elapsed, msg);
	else if (id < 10)
		printf("(%lld)\t[000%d] %s\n", elapsed, id, msg);
	else if (id < 100)
		printf("(%lld)\t[00%d] %s\n", elapsed, id, msg);
	else if (id < 1000)
		printf("(%lld)\t[0%d] %s\n", elapsed, id, msg);
	else
		printf("(%lld)\t[%d] %s\n", elapsed, id, msg);
	sem_post(g_s_speak);
}

//child function should not return 0 or above 255
int	safe_exit(int return_code)
{
	return (((return_code - 1) % 255) + 1);
}

int	child_function(int id)
{
	sem_wait(g_s_begin);
	say("i'm alive!", id);
	usleep(id * TIME_TO_WAIT);
	say("i'm living", id);
	usleep(id * TIME_TO_WAIT);
	sem_wait(g_s_eating);
	say("i'm eating", id);
	usleep(id * TIME_TO_WAIT);
	sem_post(g_s_eating);
	say("i'm slowly dying...", id);
	usleep(id * TIME_TO_WAIT);
	say("i'm dead xx", id);
	exit(safe_exit(id));
}

void	kill_all(pid_t *pid_table, int nb_philo)
{
	int	counter;

	counter = 0;
	while (counter < nb_philo)
	{
		printf("kill_all() kill pid[%d]\n", pid_table[counter]);
		kill(pid_table[counter], 9);
		counter++;
	}
}

void	main_function(pid_t *pid_table, int nb_philo)
{
	int	counter;
	int	*status;
	int	*dead_philo;
	int	nb_dead_philo;
	int	has_dead;

	say("main function begin", 0);
	dead_philo = malloc(sizeof(int) * nb_philo);
	status = malloc(sizeof(int) * nb_philo);
	counter = 0;
	has_dead = 0;
	while (counter < nb_philo)
	{
		dead_philo[counter] = 0;
		status[counter] = -1;
		counter++;
	}
	counter = 0;
	while (counter < nb_philo)
	{
		sem_post(g_s_begin);
		counter++;
	}
	while (!has_dead)
	{
		counter = 0;
		while (counter < nb_philo)
		{
			if (status[counter] == -1)
			{
				waitpid(pid_table[counter], &status[counter], WNOHANG);
				if (WIFEXITED(status[counter]))
				{
					say(" -> DEAD", counter + 1);
					kill_all(pid_table, nb_philo);
					has_dead = 1;
					break ;
				}
			}
			counter++;
		}
		usleep(CHECKTIME);
	}
	counter = 0;
	while (counter < nb_philo)
	{
		waitpid(pid_table[counter], NULL, 0);
		counter++;
	}
	say("main function end", 0);
}

int	main(int argc, char **argv)
{
	int		counter;
	int		nb_philo;
	pid_t	*pid_table;
	int		return_code;

	if (argc != 2)
	{
		printf("args\n");
		return (1);
	}
	g_begin = ft_get_timestamp_ms();
	sem_unlink("/s_begin");
	sem_unlink("/s_speak");
	sem_unlink("/s_eating");
	g_s_begin = sem_open("/s_begin", O_CREAT, S_IRWXU, 0);
	g_s_speak = sem_open("/s_speak", O_CREAT, S_IRWXU, 1);
	g_s_eating = sem_open("/s_eating", O_CREAT, S_IRWXU, 10);
	nb_philo = ft_atol(argv[1]);
	pid_table = (pid_t *)malloc(sizeof(pid_t) * nb_philo);
	counter = 0;
	while (counter < nb_philo)
	{
		pid_table[counter] = fork();
		if (!pid_table[counter])
		{
			return_code = child_function(counter + 1);
			break ;
		}
		counter++;
	}
	if (counter == nb_philo)
		main_function(pid_table, nb_philo);
	sem_close(g_s_begin);
	sem_close(g_s_speak);
	sem_close(g_s_eating);
	sem_unlink("/s_begin");
	sem_unlink("/s_speak");
	sem_unlink("/s_eating");
	if (counter == nb_philo)
		return (0);
	else
		return (return_code);
}
