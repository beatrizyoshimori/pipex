/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 19:17:05 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/22 17:02:34 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd(char *argv[], char **paths, int fd[2][2], char *envp[])
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
	dup2(fd[0][1], 1);
	close(fd[0][0]);
	close(fd[0][1]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd_infile);
	if (execve(pathname, str, envp) == -1)
	{
		free_split(str);
		free_split(paths);
		free(pathname);
		exit(1);
	}
}

void	second_cmd(char *argv[], int argc, char **paths, int fd[2][2], char *envp[], int fd_outfile)
{
	int		i;
	//int		fd_outfile;
	char	**str;
	char	*pathname;

	str = get_commands(argv[argc - 2]);
	if (access(argv[argc - 2], F_OK) == 0)
		pathname = ft_strdup(argv[argc - 2]);
	else
		pathname = get_pathname(paths, str);
	if (!pathname)
		invalid_pathname(paths, str);
	// fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	if (fd_outfile == -1)
		invalid_fd(argv[argc - 1], pathname, paths, str);
	i = (argc - 1) % 2;
	dup2(fd[i][0], 0);
	dup2(fd_outfile, 1);
	close(fd[i][0]);
	close(fd[i][1]);
	close(fd[1 - i][0]);
	close(fd[1 - i][1]);
	close(fd_outfile);
	if (execve(pathname, str, envp) == -1)
	{
		free_split(str);
		free_split(paths);
		free(pathname);
		exit(1);
	}
}

void	middle_cmd1(char *argv, char **paths, int fd[2][2], char *envp[])
{
	char	**str;
	char	*pathname;

	str = get_commands(argv);
	if (access(argv, F_OK) == 0)
		pathname = ft_strdup(argv);
	else
		pathname = get_pathname(paths, str);
	if (!pathname)
		invalid_pathname(paths, str);
	dup2(fd[1][0], 0);
	dup2(fd[0][1], 1);
	close(fd[0][0]);
	close(fd[1][1]);
	close(fd[0][0]);
	close(fd[1][1]);
	if (execve(pathname, str, envp) == -1)
	{
		free_split(str);
		free_split(paths);
		free(pathname);
		exit(1);
	}
}

void	middle_cmd2(char *argv, char **paths, int fd[2][2], char *envp[])
{
	char	**str;
	char	*pathname;

	str = get_commands(argv);
	if (access(argv, F_OK) == 0)
		pathname = ft_strdup(argv);
	else
		pathname = get_pathname(paths, str);
	if (!pathname)
		invalid_pathname(paths, str);
	dup2(fd[0][0], 0);
	dup2(fd[1][1], 1);
	close(fd[0][0]);
	close(fd[1][1]);
	close(fd[0][0]);
	close(fd[1][1]);
	if (execve(pathname, str, envp) == -1)
	{
		free_split(str);
		free_split(paths);
		free(pathname);
		exit(1);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		fd[2][2];
	int		pid[argc - 3];
	char	**paths;
	int		fd_outfile;

	paths = get_paths(envp);
	if (pipe(fd[0]) == -1)
		return (free_split(paths), 1);
	if (pipe(fd[1]) == -1)
		return (free_split(paths), 1);
	fd_outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0777);
	i = 0;
	while (i < argc - 3)
	{
		if (i == 0)
		{
			pid[i] = fork();
			if (pid[i] < 0)
				return (close_pipe_free_paths(fd, paths), 1);
			else if (pid[i] == 0)
				first_cmd(argv, paths, fd, envp);			
			close_pipes(fd);
		}
		else if (i < argc - 4)
		{
			pid[i] = fork();
			if (pid[i] < 0)
				return (close_pipe_free_paths(fd, paths), 1);
			else if (pid[i] == 0)
			{
				if (i % 2 == 0)
					middle_cmd1(argv[i + 2], paths, fd, envp);
				else
					middle_cmd2(argv[i + 2], paths, fd, envp);
			}
			close_pipes(fd);
		}
		else
		{
			pid[i] = fork();
			if (pid[i] < 0)
				return (close_pipe_free_paths(fd, paths), 1);
			else if (pid[i] == 0)
				second_cmd(argv, argc, paths, fd, envp, fd_outfile);
			close_pipes(fd);
		}
		i++;
	}
	close_pipes(fd);
	free_split(paths);
	int status;
	i = 0;
	while (i < argc - 3)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	int exit_status = WEXITSTATUS(status);  
	return (exit_status);
}
