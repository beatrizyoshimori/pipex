/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/25 15:11:00 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	execve_error(t_data *data, char **str, char *pathname)
{
	free_split(str);
	free_split(data->paths);
	free(data->pid);
	free(data);
	free(pathname);
	exit(1);
}

void	pipe_error(t_data *data)
{
	close_pipes(data->fd);
	free_all(data);
	exit(1);
}
