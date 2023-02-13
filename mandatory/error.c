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

void	invalid_pathname(t_data *data, char *cmd)
{
	ft_putstr_fd("bash: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putstr_fd(": command not found\n", 1);
	free_all(data);
	exit(127);
}

void	invalid_fd(char *argv, t_data *data)
{
	ft_putstr_fd("bash: ", 1);
	perror(argv);
	free_all(data);
	exit(1);
}

void	execve_error(t_data *data)
{
	free_all(data);
	exit(1);
}

void	fork_error(t_data *data)
{
	ft_putstr_fd("Fork error.\n", 1);
	close(data->fd[0]);
	close(data->fd[1]);
	free_all(data);
	exit(1);
}

void	pipe_error(t_data *data)
{
	ft_putstr_fd("Pipe error.\n", 1);
	free_all(data);
	exit(1);
}
