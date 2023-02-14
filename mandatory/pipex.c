/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 17:10:51 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	make_command(t_data *data, char *argv, int fd)
{
	check_empty_string(argv, data, fd);
	data->command = get_commands(argv);
	if (access(argv, F_OK) == 0)
	{
		check_execution_permission(argv);
		data->pathname = ft_strdup(argv);
	}
	else
		data->pathname = get_pathname(data->paths, data->command);
	if (!data->pathname)
		invalid_pathname(data, argv);
}

void	first_cmd(char *argv[], char *envp[], t_data *data)
{
	int		fd_infile;

	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		invalid_fd(argv[1], data);
	make_command(data, argv[2], fd_infile);
	close(data->fd[0]);
	dup2(fd_infile, 0);
	dup2(data->fd[1], 1);
	close(data->fd[1]);
	close(fd_infile);
	if (execve(data->pathname, data->command, envp) == -1)
		execve_error(data);
}

void	second_cmd(char *argv[], char *envp[], t_data *data)
{
	int		fd_outfile;

	fd_outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd_outfile == -1)
		invalid_fd(argv[4], data);
	make_command(data, argv[3], fd_outfile);
	close(data->fd[1]);
	dup2(data->fd[0], 0);
	dup2(fd_outfile, 1);
	close(data->fd[0]);
	close(fd_outfile);
	if (execve(data->pathname, data->command, envp) == -1)
		execve_error(data);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		exit_status;
	t_data	*data;

	check_args(argc);
	get_data(&data, envp);
	if (pipe(data->fd) == -1)
		pipe_error(data);
	data->pid[0] = fork();
	if (data->pid[0] < 0)
		fork_error(data);
	else if (data->pid[0] == 0)
		first_cmd(argv, envp, data);
	data->pid[1] = fork();
	if (data->pid[1] < 0)
		fork_error(data);
	if (data->pid[1] == 0)
		second_cmd(argv, envp, data);
	close(data->fd[0]);
	close(data->fd[1]);
	waitpid(data->pid[0], &data->status, 0);
	waitpid(data->pid[1], &data->status, 0);
	exit_status = WEXITSTATUS(data->status);
	free_all(data);
	return (exit_status);
}
