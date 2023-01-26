/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 19:00:45 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/26 19:21:26 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	invalid_pathname(char **paths, char **str)
{
	perror("command not found");
	free_split(paths);
	free_split(str);
	exit(127);
}

void	invalid_fd(char *argv, char *pathname, char **paths, char **str)
{
	perror(argv);
	if (pathname)
		free(pathname);
	free_split(str);
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
	close(fd[0]);
	close(fd[1]);
	free_split(paths);
	exit(1);
}

void	pipe_error(char **paths)
{
	free_split(paths);
	exit(1);
}
