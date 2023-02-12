/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 16:28:47 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	close_pipe_free_paths(int fd[], char **paths)
{
	close(fd[0]);
	close(fd[1]);
	free_split(paths);
}

void	check_empty_string(char *argv, char **paths, int fd)
{
	if (ft_strlen(argv) == 0)
	{
		ft_putstr_fd("bash: : command not found\n", 1);
		free_split(paths);
		close(fd);
		exit(127);
	}
}

void	check_args(int argc)
{
	if (argc != 5)
	{
		ft_putstr_fd("Invalid number of arguments.\n", 1);
		ft_putstr_fd("Usage: ./pipex file1 cmd1 cmd2 file2\n", 1);
		exit(1);
	}
}
