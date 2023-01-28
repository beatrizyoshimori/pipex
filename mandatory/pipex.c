/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/26 19:48:01 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(char *argv[], char **paths, int fd[], char *envp[])
{
	int		fd_infile;
	char	**str;
	char	*pathname;

	str = get_commands(argv[2]);
	if (access(argv[2], F_OK) == 0)
		pathname = ft_strdup(argv[2]);
	else
		pathname = get_pathname(paths, str);
	if (!pathname)
		invalid_pathname(paths, str);
	fd_infile = open(argv[1], O_RDONLY);
	if (fd_infile == -1)
		invalid_fd(argv[1], pathname, paths, str);
	dup2(fd_infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(fd_infile);
	if (execve(pathname, str, envp) == -1)
		execve_error(pathname, paths, str);
}

void	second_cmd(char *argv[], char **paths, int fd[], char *envp[])
{
	int		fd_outfile;
	char	**str;
	char	*pathname;

	str = get_commands(argv[3]);
	if (access(argv[3], F_OK) == 0)
		pathname = ft_strdup(argv[3]);
	else
		pathname = get_pathname(paths, str);
	if (!pathname)
		invalid_pathname(paths, str);
	fd_outfile = open(argv[4], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_outfile == -1)
		invalid_fd(argv[4], pathname, paths, str);
	dup2(fd[0], 0);
	dup2(fd_outfile, 1);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	if (execve(pathname, str, envp) == -1)
		execve_error(pathname, paths, str);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	pid_t	pid[2];
	int		status;
	int		exit_status;
	char	**paths;

	paths = get_paths(envp);
	if (argc != 5 || pipe(fd) == -1)
		pipe_error(paths);
	pid[0] = fork();
	if (pid[0] < 0)
		fork_error(fd, paths);
	else if (pid[0] == 0)
		first_cmd(argv, paths, fd, envp);
	pid[1] = fork();
	if (pid[1] < 0)
		fork_error(fd, paths);
	if (pid[1] == 0)
		second_cmd(argv, paths, fd, envp);
	close_pipe_free_paths(fd, paths);
	waitpid(pid[0], &status, 0);
	waitpid(pid[1], &status, 0);
	exit_status = WEXITSTATUS(status);
	return (exit_status);
}
