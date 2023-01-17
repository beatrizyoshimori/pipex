/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/16 21:28:43 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_cmd(char *argv[], char **paths, int fd[])
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
		invalid_fd(argv[1], pathname, str);
	dup2(fd_infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	close(fd_infile);
	if (execve(pathname, str, NULL) == -1)
		free_split(str);
}

void	second_cmd(char *argv[], char **paths, int fd[])
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
		invalid_fd(argv[4], pathname, str);
	dup2(fd[0], 0);
	dup2(fd_outfile, 1);
	close(fd[0]);
	close(fd[1]);
	close(fd_outfile);
	if (execve(pathname, str, NULL) == -1)
		free_split(str);
}

void	close_pipe_free_paths(int fd[], char ***paths)
{
	close(fd[0]);
	close(fd[1]);
	free_split(*paths);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd[2];
	int		pid;
	int		pid2;
	char	**paths;

	paths = get_paths(envp);
	if (argc != 5 || pipe(fd) == -1)
		return (free_split(paths), 1);
	pid = fork();
	if (pid < 0)
		return (close_pipe_free_paths(fd, &paths), 1);
	else if (pid == 0)
	{
		first_cmd(argv, paths, fd);
		free_split(paths);
		//close_pipe_free_paths(fd, &paths);
		close(fd[0]);
		close(fd[1]);
		exit(1);
	}
	pid2 = fork();
	if (pid2 < 0)
		return (close_pipe_free_paths(fd, &paths), 1);
	if (pid2 == 0)
		second_cmd(argv, paths, fd);
	//close_pipe_free_paths(fd, paths);
	close(fd[0]);
	close(fd[1]);	
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_split(paths);
	return (0);
}
