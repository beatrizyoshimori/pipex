/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/26 18:35:08 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_data
{
	int		fd[2][2];
	pid_t	*pid;
	char	**paths;
	int		status;
	int		exit_status;
	int		num_cmds;
	char	*pathname;
	char	**str;
}	t_data;

void	first_cmd(char *argv[], t_data *data);
void	last_cmd(char *argv[], t_data *data, int i);
void	middle_cmd(t_data *data, int i);
char	**get_commands(char *str);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);
void	free_all(t_data *data);
void	invalid_pathname(char **paths, char **str);
void	invalid_fd(char *argv, char *pathname, char **paths, char **str);
void	close_pipes_free_all(t_data *data);
void	close_pipes(int fd[2][2]);
void	execve_error(t_data *data);
void	fork_error(t_data *data);
void	get_data(t_data **data, int argc, char *envp[]);
void	recycle_pipe(t_data *data, int i);
void	start_pipes(t_data *data);

#endif