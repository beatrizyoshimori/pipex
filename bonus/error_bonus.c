/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 14:52:51 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 19:21:29 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	close_pipes(data->fd);
	free_all(data);
	exit(1);
}

void	check_args(int argc)
{
	if (argc < 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 1);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 cmd[n] file2\n", 1);
		exit(1);
	}
}
