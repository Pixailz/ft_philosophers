/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:45:28 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/10 02:37:13 by brda-sil         ###   ########.fr       */
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

#define DEMISEC 20000
// #define CHECKTIME 500

// void	pseudo_life(int id)
// {
// 	printf("%d: i'm alive!\n", id);
// 	usleep(id * DEMISEC);
// 	printf("%d: i'm living\n", id);
// 	usleep(id * DEMISEC);
// 	printf("%d: i'm eating\n", id);
// 	usleep(id * DEMISEC);
// 	printf("%d: i'm slowly dying...\n", id);
// 	usleep(id * DEMISEC);
// 	printf("%d: i'm dead xx\n", id);
// }

// void	death_checker(pid_t *pid_table, int nb_philo)
// {
// 	int	counter;
// 	int	*status;
// 	int	*dead_philo;
// 	int	nb_dead_philo;

// 	dead_philo = malloc(sizeof(int) * nb_philo);
// 	status = malloc(sizeof(int) * nb_philo);
// 	counter = 0;
// 	while (counter < nb_philo)
// 	{
// 		dead_philo[counter] = 0;
// 		status[counter] = 1;
// 		counter++;
// 	}
// 	printf("Here come the death.\n");
// 	while (1)
// 	{
// 		counter = 0;
// 		while (counter < nb_philo)
// 		{
// 			waitpid(pid_table[counter], &status[counter], WNOHANG);
// 			if (WIFEXITED(status[counter]))
// 			{
// 				printf("%d -> dead\n", counter + 1);
// 				dead_philo[counter] = 1;
// 			}
// 			counter++;
// 		}
// 		counter = 0;
// 		nb_dead_philo = 0;
// 		while (counter < nb_philo)
// 		{
// 			if (dead_philo[counter])
// 				nb_dead_philo++;
// 			counter++;
// 		}
// 		if (nb_dead_philo == nb_philo)
// 			break ;
// 		usleep(CHECKTIME);
// 	}
// }

// int	main(int argc, char **argv)
// {
// 	int		counter;
// 	int		nb_philo;
// 	pid_t	*pid_table;

// 	srand(time(NULL));
// 	if (argc != 2)
// 	{
// 		printf("args\n");
// 		return (1);
// 	}
// 	nb_philo = ft_atol(argv[1]);
// 	pid_table = (pid_t *)malloc(sizeof(pid_t) * nb_philo);
// 	counter = 0;
// 	while (counter < nb_philo)
// 	{
// 		pid_table[counter] = fork();
// 		if (!pid_table[counter])
// 		{
// 			pseudo_life(counter + 1);
// 			break ;
// 		}
// 		counter++;
// 	}
// 	if (counter == nb_philo)
// 		death_checker(pid_table, nb_philo);
// 	return (0);
// }

long int	ft_atol(char *str);
long long	ft_get_timestamp_ms(void);

sem_t		*s_begin;
sem_t		*s_speak;
sem_t		*s_eating;

long long	begin;

void	say(char *msg, int id)
{
	long long	elapsed;

	elapsed = ft_get_timestamp_ms() - begin;
	sem_wait(s_speak);
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
	sem_post(s_speak);
}

void	child_function(int id)
{
	sem_wait(s_begin);
	say("i'm alive!", id);
	usleep(id * DEMISEC);
	say("i'm living", id);
	usleep(id * DEMISEC);
	sem_wait(s_eating);
	say("i'm eating", id);
	usleep(id * DEMISEC);
	sem_post(s_eating);
	say("i'm slowly dying...", id);
	usleep(id * DEMISEC);
	say("i'm dead xx", id);
}

void	main_function(pid_t *pid_table, int nb_philo)
{
	int	counter;

	say("main function begin", 0);
	counter = 0;
	while (counter < nb_philo)
	{
		sem_post(s_begin);
		counter++;
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

	if (argc != 2)
	{
		printf("args\n");
		return (1);
	}
	begin = ft_get_timestamp_ms();
	sem_unlink("/s_begin");
	sem_unlink("/s_speak");
	sem_unlink("/s_eating");
	s_begin = sem_open("/s_begin", O_CREAT, S_IRWXU, 0);
	s_speak = sem_open("/s_speak", O_CREAT, S_IRWXU, 1);
	s_eating = sem_open("/s_eating", O_CREAT, S_IRWXU, 1);
	counter = 0;
	nb_philo = ft_atol(argv[1]);
	pid_table = malloc(sizeof(pid_t) * nb_philo);
	while (counter < nb_philo)
	{
		pid_table[counter] = fork();
		if (!pid_table[counter])
		{
			child_function(counter + 1);
			break ;
		}
		counter++;
	}
	if (counter == nb_philo)
		main_function(pid_table, nb_philo);
	sem_close(s_begin);
	sem_close(s_speak);
	sem_close(s_eating);
	sem_unlink("/s_begin");
	sem_unlink("/s_speak");
	sem_unlink("/s_eating");
	return (0);
}
