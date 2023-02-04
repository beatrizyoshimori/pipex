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
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

void	first_cmd(char *argv[], char **paths, int fd[], char *envp[]);
void	second_cmd(char *argv[], char **paths, int fd[], char *envp[]);
void	delete_quotes(char **split_str);
char	**get_commands(char *str);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);
void	close_pipe_free_paths(int fd[], char **paths);
void	check_empty_string(char *argv, char **paths, int fd);
void	invalid_pathname(char **paths, char **str);
void	invalid_fd(char *argv, char **paths);
void	execve_error(char *pathname, char **paths, char **str);
void	fork_error(int fd[2], char **paths);
void	pipe_error(char **paths);

#endif