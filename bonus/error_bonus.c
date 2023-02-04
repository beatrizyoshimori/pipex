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

void	invalid_pathname(t_data *data)
{
	perror("command not found");
	free_all(data);
	exit(127);
}

void	invalid_fd(char *argv, t_data *data)
{
	perror(argv);
	free_all(data);
	exit(1);
}

void	execve_error(t_data *data)
{
	free_all(data);
	exit(126);
}

void	fork_error(t_data *data)
{
	close_pipes(data->fd);
	free_all(data);
	exit(1);
}
