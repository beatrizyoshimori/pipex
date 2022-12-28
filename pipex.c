/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teste.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2022/12/28 19:40:00 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

int	main(int argc, char *argv[])
{
	int		fd[2];
	int		pid;
	int		pid2;
	char	**str;
	char	**str2;

	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		//char *str[] = {"ls", "-l", NULL};
		str = ft_split(argv[1], ' ');
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execvp("ls", str);
		free(str);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		//char *str2[] = {"grep", "txt", NULL};
		str2 = ft_split(argv[2], ' ');
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execvp("grep", str2);
		free(str2);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
}
