/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/22 16:42:14 by byoshimo         ###   ########.fr       */
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

void	first_cmd(char *argv[], char **paths, int fd[2][2], char *envp[]);
void	second_cmd(char *argv[], int argc, char **paths, int fd[2][2], char *envp[]);
char	**get_commands(char *str);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);
void	invalid_pathname(char **paths, char **str);
void	invalid_fd(char *argv, char *pathname, char **paths, char **str);
void	close_pipe_free_paths(int fd[2][2], char **paths);
void	close_pipes(int fd[2][2]);

#endif