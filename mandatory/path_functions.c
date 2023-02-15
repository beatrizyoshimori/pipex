/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:49:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/15 20:30:12 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_execution_permission(char *pathname, t_data *data)
{
	if (access(pathname, X_OK) == -1)
	{
		close(data->fd[0]);
		close(data->fd[1]);
		perror(pathname);
		free_all(data);
		exit(126);
	}
}

void	get_pathname(t_data *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i], "/");
		data->pathname = ft_strjoin(tmp, data->command[0]);
		if (tmp)
			free(tmp);
		if (access(data->pathname, F_OK) == 0)
		{
			check_execution_permission(data->pathname, data);
			return ;
		}
		if (data->pathname)
			free(data->pathname);
		i++;
	}
	data->pathname = NULL;
}

char	**get_paths(char *envp[])
{
	char	*tmp;
	char	*tmp2;
	char	**paths;

	while (envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break ;
		envp++;
	}
	tmp = ft_strdup(*envp);
	tmp2 = ft_strtrim(tmp, "PATH=");
	paths = ft_split(tmp2, ':');
	free(tmp);
	free(tmp2);
	return (paths);
}
