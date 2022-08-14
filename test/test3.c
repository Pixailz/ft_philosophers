/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 05:52:18 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 11:37:29 by brda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
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

typedef struct s_test
{
	pid_t		*pid;
	int			nb_child;
	char		**str;
	sem_t		*s_test;
}				t_test;

void	free_entry(t_test *test)
{
	printf("free func\n");
	free(test->str[0]);
	free(test->str[1]);
	free(test->str[2]);
	free(test->str[3]);
	free(test->str);
	free(test->pid);
	sem_unlink("/s_test");
	sem_close(test->s_test);
}

void	child_process(t_test *test)
{
	printf("child %p\n", test);
	printf("child %d\n", getpid());
	sleep(4);
	free_entry(test);
}

void	parent_process(t_test *test)
{
	int	counter;

	printf("parent %p\n", test);
	printf("parent %d\n", getpid());
	sleep(1);
	counter = 0;
	while (counter < test->nb_child)
		kill(test->pid[counter++], 9);
	counter = 0;
	while (counter < test->nb_child)
		waitpid(test->pid[counter++], NULL, 0);
	free_entry(test);
}

void	init(t_test *test, int nb_child)
{
	test->str = (char **)malloc(sizeof(char *) * 4);
	test->str[0] = (char *)malloc(sizeof(char) * 12);
	test->str[1] = (char *)malloc(sizeof(char) * 12);
	test->str[2] = (char *)malloc(sizeof(char) * 12);
	test->str[3] = (char *)malloc(sizeof(char) * 12);
	test->pid = (pid_t *)malloc(sizeof(pid_t) * nb_child);
	strcpy(test->str[0], "Hello World");
	strcpy(test->str[1], "Hello World");
	strcpy(test->str[2], "Hello World");
	strcpy(test->str[3], "Hello World");
	test->nb_child = nb_child;
	sem_unlink("/s_test");
	test->s_test = sem_open("/s_test", O_CREAT, 0666, 1);
}

int	main(int argc, char **argv)
{
	t_test	test;
	int		counter;

	if (argc != 2)
		return (printf("args\n"));
	init(&test, atoi(argv[1]));
	counter = 0;
	while (counter < test.nb_child)
	{
		test.pid[counter] = fork();
		if (test.pid[counter] == 0)
		{
			child_process(&test);
			break ;
		}
		counter++;
	}
	if (counter == test.nb_child)
		parent_process(&test);
	return (0);
}
