/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/24 21:45:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	free_all(t_data *data)
{
	free_split(data->paths);
	free(data->pid);
	free(data);
}

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

void	close_pipes_free_all(t_data *data)
{
	close(data->fd[0][1]);
	close(data->fd[0][0]);
	close(data->fd[1][0]);
	close(data->fd[1][1]);
	free_all(data);
}

void	close_pipes(int fd[2][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
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

void	get_data(t_data **data, int argc, char *envp[])
{
	(*data) = malloc(sizeof(t_data));
	if (!*data)
		return ;
	(*data)->num_cmds = argc - 3;
	(*data)->pid = malloc(sizeof(int) * (*data)->num_cmds);
	if (!(*data)->pid)
	{
		free(*data);
		return ;
	}
	(*data)->paths = get_paths(envp);
	if (!(*data)->paths)
	{
		free((*data)->pid);
		free((*data));
		return ;
	}
}

void	recycle_pipe(t_data *data, int fd)
{
	close(data->fd[fd][0]);
	close(data->fd[fd][1]);
	if (pipe(data->fd[fd]) == -1)
	{
		free_all(data);
		exit(127);
	}
}

void	start_pipes(t_data *data)
{
	if (pipe(data->fd[0]) == -1)
	{
		free_all(data);
		exit(127);
	}
	if (pipe(data->fd[1]) == -1)
	{
		free_all(data);
		exit(127);
	}
}