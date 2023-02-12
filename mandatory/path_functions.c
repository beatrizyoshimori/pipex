/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:49:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/17 17:54:29 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	check_execution_permission(char *pathname)
{
	if (access(pathname, X_OK) == -1)
	{
		ft_putstr_fd("bash: ", 1);
		perror(pathname);
		exit(126);
	}
}

char	*get_pathname(char **paths, char **str)
{
	int		i;
	char	*tmp;
	char	*pathname;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(tmp, str[0]);
		if (tmp)
			free(tmp);
		if (access(pathname, F_OK) == 0)
		{
			check_execution_permission(pathname);
			return (pathname);
		}
		if (pathname)
			free(pathname);
		i++;
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
