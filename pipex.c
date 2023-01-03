/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/03 20:15:06 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;
	int		pid2;
	char	**str;
	char	**str2;
	char	**paths;
	char	*tmp;
	char	*pathname;
	int		i;
	int		fd_outfile;
	int		fd_infile;

	//printf("%s\n", envp[22]);
	paths = ft_split(ft_strtrim(ft_strdup(envp[22]), "PATH="), ':');
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		str = ft_split(argv[1], ' ');
		i = 0;
		while(paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			pathname = ft_strjoin(tmp, str[0]);
			free(tmp);
			if (access(pathname, F_OK) == 0)
				break ;
			free(pathname);
			i++;
		}
		fd_infile = open("file1.txt", O_RDONLY);
		dup2(fd_infile, 0);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		free(paths);
		execve(pathname, str, NULL);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		str2 = ft_split(argv[2], ' ');
		i = 0;
		while(paths[i])
		{
			tmp = ft_strjoin(paths[i], "/");
			pathname = ft_strjoin(tmp, str2[0]);
			free(tmp);
			if (access(pathname, F_OK | X_OK) == 0)
				break ;
			free(pathname);
			i++;
		}
		fd_outfile = open("file2", O_WRONLY);
		dup2(fd[0], 0);
		dup2(fd_outfile, 1);
		close(fd[0]);
		close(fd[1]);
		free(paths);
		execve(pathname, str2, NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free(paths);
}
