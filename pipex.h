/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:49 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/13 20:05:20 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>

# include <unistd.h>
# include <sys/wait.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include "libft/libft.h"

void	first_cmd(char *argv[], char **paths, int fd[]);
void	second_cmd(char *argv[], char **paths, int fd[]);
char	**get_commands(char *str);
char	*get_pathname(char **paths, char **str);
char	**get_paths(char *envp[]);
void	free_split(char **str);

#endif