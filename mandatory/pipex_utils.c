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

void	free_all(t_data *data)
{
	if (data->pathname)
		free(data->pathname);
	if (data->paths)
		free_split(data->paths);
	if (data->command)
		free_split(data->command);
	if (data)
		free(data);
}

void	get_data(t_data **data, char *envp[])
{
	(*data) = (t_data *)malloc(sizeof(t_data));
	if (!*data)
	{
		ft_putstr_fd("Could not allocate data.\n", 1);
		exit(1);
	}
	(*data)->command = NULL;
	(*data)->pathname = NULL;
	(*data)->paths = get_paths(envp);
	if (!(*data)->paths)
	{
		free((*data));
		exit(1);
	}
}

void	check_empty_string(char *argv, t_data *data, int fd)
{
	if (ft_strlen(argv) == 0)
	{
		ft_putstr_fd("bash: : command not found\n", 1);
		close(data->fd[0]);
		close(data->fd[1]);
		close(fd);
		free_all(data);
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
