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

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char	**get_paths(char *envp[])
{
	char	*tmp;
	char	**paths;

	while (envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break;
		envp++;
	}
	tmp = ft_strdup(*envp);
	tmp = ft_strtrim(tmp, "PATH=");
	paths = ft_split(tmp, ':');
	free(tmp);
	return (paths);
}

void	first_cmd(char *argv[], char **paths, int fd[])
{
	int		i;
	int		fd_infile;
	char	**str;
	char	*tmp;
	char	*pathname;

	str = ft_split(argv[2], ' ');
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
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
	{
		free(pathname);
		free_split(str);
	}
	dup2(fd_infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	execve(pathname, str, NULL);
	free(pathname);
	free_split(str);
}

void	second_cmd(char *argv[], char **paths, int fd[])
{
	int		i;
	int		fd_outfile;
	char	**str;
	char	*tmp;
	char	*pathname;

	str = ft_split(argv[3], ' ');
	i = 0;
	while(paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(tmp, str[0]);
		free(tmp);
		if (access(pathname, F_OK | X_OK) == 0)
			break ;
		free(pathname);
		i++;
	}
	fd_outfile = open(argv[4], O_WRONLY | O_TRUNC);
	if (fd_outfile == -1)
	{
		free(pathname);
		free_split(str);
	}
	dup2(fd[0], 0);
	dup2(fd_outfile, 1);
	close(fd[0]);
	close(fd[1]);
	execve(pathname, str, NULL);
	free(pathname);
	free_split(str);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;
	//int		pid2;
	char	**paths;

	paths = get_paths(envp);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	printf("pid1: %i\n", pid);
	if (pid < 0)
		return (1);
	else if (pid == 0)
		first_cmd(argv, paths, fd);
	second_cmd(argv, paths, fd);
	// pid2 = fork();
	// if (pid2 < 0)
	// 	return (1);
	// if (pid2 == 0)
	// 	second_cmd(argv, paths, fd);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid, NULL, 0);
	//waitpid(pid2, NULL, 0);
	free_split(paths);
}
