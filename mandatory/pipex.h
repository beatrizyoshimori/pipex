/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 16:28:52 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		fd[2];
	pid_t	pid[2];
	char	**paths;
	int		status;
	char	*pathname;
	char	**command;
}	t_data;

void	make_command(t_data *data, char *argv, int fd);
void	first_cmd(char *argv[], char *envp[], t_data *data);
void	second_cmd(char *argv[], char *envp[], t_data *data);
void	delete_quotes(char **split_str);
char	**get_commands(char *str);
void	check_execution_permission(char *pathname);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);
void	free_all(t_data *data);
void	get_data(t_data **data, char *envp[]);
void	check_empty_string(char *argv, t_data *data, int fd);
void	check_args(int argc);
void	invalid_pathname(t_data *data, char *cmd);
void	invalid_fd(char *argv, t_data *data);
void	execve_error(t_data *data);
void	fork_error(t_data *data);
void	pipe_error(t_data *data);

#endif