/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 19:19:59 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (data->str)
		free_split(data->str);
	if (data->pid)
		free(data->pid);
	if (data)
		free(data);
}

void	get_data(t_data **data, int argc, char *envp[])
{
	(*data) = malloc(sizeof(t_data));
	if (!*data)
		return ;
	(*data)->num_cmds = argc - 3;
	(*data)->pid = malloc(sizeof(int) * (*data)->num_cmds);
	if (!(*data)->pid)
	{
		free(*data);
		exit(1);
	}
	(*data)->paths = get_paths(envp);
	if (!(*data)->paths)
	{
		free((*data)->pid);
		free((*data));
		exit(1);
	}
}

void	check_empty_string(char *argv[], t_data *data, int i)
{
	int	fd;

	fd = 0;
	if (ft_strlen(argv[i + 2]) == 0)
	{
		if (i == 0)
		{
			fd = open(argv[1], O_RDONLY);
			if (fd == -1)
				invalid_fd(argv[1], data);
			close(fd);
		}
		if (i == data->num_cmds - 1)
		{
			fd = open(argv[i + 3], O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if (fd == -1)
				invalid_fd(argv[i + 3], data);
			close(fd);
		}
		close_pipes(data->fd);
		free_all(data);
		perror("zsh: permission denied");
		exit(126);
	}
}
