/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brda-sil <brda-sil@students.42angouleme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 05:52:18 by brda-sil          #+#    #+#             */
/*   Updated: 2022/08/14 05:58:40 by brda-sil         ###   ########.fr       */
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

void	free_entry(char *str)
{
	free(str);
}

void	child_process(char *str)
{
	sleep(7);
	free_entry(str);
}

void	parent_process(char *str, pid_t pid)
{
	sleep(5);
	kill(pid, 9);
	free_entry(str);
}

int	main(int argc, char **argv)
{
	char	*str;
	pid_t	pid;

	str = (char *)malloc(sizeof(char) * 14);
	strcpy(str, "Hello Worlds\n");
	pid = fork();
	if (pid == 0)
		child_process(str);
	else
		parent_process(str, pid);
	return (0);
}
