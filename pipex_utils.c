/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/17 22:22:17 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	str = NULL;
}

void	invalid_pathname(char **paths, char **str)
{
	perror("command not found");
	free_split(paths);
	free_split(str);
	exit(128);
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

void	close_pipe_free_paths(int fd[], char **paths)
{
	close(fd[0]);
	close(fd[1]);
	free_split(paths);
}
