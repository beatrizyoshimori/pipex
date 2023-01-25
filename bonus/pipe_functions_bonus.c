/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 15:02:36 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/25 15:10:32 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	recycle_pipe(t_data *data, int i)
{
	int	fd;

	if (i % 2 == 0)
		fd = 1;
	else
		fd = 0;
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

void	close_pipes(int fd[2][2])
{
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
}
