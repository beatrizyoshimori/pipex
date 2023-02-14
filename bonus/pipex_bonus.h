/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 19:21:45 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		fd[2][2];
	pid_t	*pid;
	char	**paths;
	int		status;
	int		num_cmds;
	char	*pathname;
	char	**command;
}	t_data;

void	first_cmd(char *argv[], t_data *data);
void	last_cmd(char *argv[], t_data *data, int i);
void	middle_cmd(t_data *data, int i);
void	child_process(char *argv[], char *envp[], t_data *data, int i);
void	delete_quotes(char **split_str);
char	**get_commands(char *str);
void	check_execution_permission(char *pathname);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);
void	free_all(t_data *data);
void	get_data(t_data **data, int argc, char *envp[]);
void	check_file1_and_empty_string(char *argv[], t_data *data, int i);
void	invalid_pathname(t_data *data, char *cmd);
void	invalid_fd(char *argv, t_data *data);
void	execve_error(t_data *data);
void	fork_error(t_data *data);
void	check_args(int argc);
void	recycle_pipe(t_data *data, int i);
void	start_pipes(t_data *data);
void	close_pipes(int fd[2][2]);

#endif