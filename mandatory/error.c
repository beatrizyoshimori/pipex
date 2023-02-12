/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:00:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 14:51:54 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	invalid_pathname(char **paths, char **str, char *cmd)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	free_split(paths);
	free_split(str);
	exit(127);
}

void	invalid_fd(char *argv, char **paths)
{
	ft_putstr_fd("bash: ", 1);
	perror(argv);
	free_split(paths);
	exit(1);
}

void	execve_error(char *pathname, char **paths, char **str)
{
	free_split(str);
	free_split(paths);
	free(pathname);
	exit(1);
}

void	fork_error(int fd[2], char **paths)
{
	ft_putstr_fd("Fork error.\n", 1);
	close(fd[0]);
	close(fd[1]);
	free_split(paths);
	exit(1);
}

void	pipe_error(char **paths)
{
	ft_putstr_fd("Pipe error.\n", 1);
	free_split(paths);
	exit(1);
}
