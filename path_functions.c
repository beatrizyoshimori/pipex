/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:49:17 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/13 19:54:15 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_pathname(char **paths, char **str)
{
	int		i;
	char	*tmp;
	char	*pathname;

	i = 0;
	while(paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		pathname = ft_strjoin(tmp, str[0]);
		free(tmp);
		if (access(pathname, F_OK) == 0)
			break ;
		free(pathname);
		i++;
	}
	return (pathname);
}

char	**get_paths(char *envp[])
{
	char	*tmp;
	char	*tmp2;
	char	**paths;

	while (envp)
	{
		if (ft_strnstr(*envp, "PATH=", 5))
			break;
		envp++;
	}
	tmp = ft_strdup(*envp);
	tmp2 = ft_strtrim(tmp, "PATH=");
	paths = ft_split(tmp2, ':');
	free(tmp);
	free(tmp2);
	return (paths);
}
