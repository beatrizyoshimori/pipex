/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/25 16:33:14 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(char *argv[], t_data *data)
{
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		invalid_fd(argv[1], data->pathname, data->paths, data->str);
	dup2(fd_infile, 0);
	dup2(data->fd[0][1], 1);
	close_pipes(data->fd);
	close(fd_infile);
}

void	last_cmd(char *argv[], t_data *data, int i)
{
	int		fd;
	int		fd_outfile;

	fd_outfile = open(argv[i + 3], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_outfile == -1)
		invalid_fd(argv[i + 3], data->pathname, data->paths, data->str);
	fd = (i + 3) % 2;
	dup2(data->fd[fd][0], 0);
	dup2(fd_outfile, 1);
	close_pipes(data->fd);
	close(fd_outfile);
}

void	middle_cmd(t_data *data, int i)
{
	if (i % 2 == 0)
	{
		dup2(data->fd[1][0], 0);
		dup2(data->fd[0][1], 1);
	}
	else
	{
		dup2(data->fd[0][0], 0);
		dup2(data->fd[1][1], 1);
	}
	close_pipes(data->fd);
}

void	child_process(char *argv[], char *envp[], t_data *data, int i)
{
	data->str = get_commands(argv[i + 2]);
	if (access(argv[i + 2], F_OK) == 0)
		data->pathname = ft_strdup(argv[i + 2]);
	else
		data->pathname = get_pathname(data->paths, data->str);
	if (!data->pathname)
		invalid_pathname(data->paths, data->str);
	if (i == 0)
		first_cmd(argv, data);
	else if (i < data->num_cmds - 1)
		middle_cmd(data, i);
	else
		last_cmd(argv, data, i);
	if (execve(data->pathname, data->str, envp) == -1)
		execve_error(data);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		exit_status;
	t_data	*data;

	get_data(&data, argc, envp);
	start_pipes(data);
	i = 0;
	while (i < data->num_cmds)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
			pipe_error(data);
		else if (data->pid[i] == 0)
			child_process(argv, envp, data, i);
		if (i < argc - 4)
			recycle_pipe(data, i);
		i++;
	}
	close_pipes(data->fd);
	i = 0;
	while (i < argc - 3)
		waitpid(data->pid[i++], &data->status, 0);
	exit_status = WEXITSTATUS(data->status);
	free_all(data);
	return (exit_status);
}
