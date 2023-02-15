/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:49:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/14 20:52:27 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	check_execution_permission(char *pathname, t_data *data)
{
	if (access(pathname, X_OK) == -1)
	{
		perror(pathname);
		close_pipes(data->fd);
		free_all(data);
		exit(126);
	}
}

char	*get_pathname(t_data *data)
{
	int		i;
	char	*tmp;
	char	*pathname;

	i = 0;
	while (data->paths[i])
	{
		tmp = ft_strjoin(data->paths[i++], "/");
		pathname = ft_strjoin(tmp, data->command[0]);
		if (tmp)
			free(tmp);
		if (access(pathname, F_OK) == 0)
		{
			check_execution_permission(pathname, data);
			return (pathname);
		}
		if (pathname)
			free(pathname);
	}
	return (NULL);
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
