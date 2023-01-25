/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:55:13 by byoshimo          #+#    #+#             */
/*   Updated: 2023/01/25 15:03:26 by byoshimo         ###   ########.fr       */
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
	free_split(data->paths);
	free(data->pid);
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
		return ;
	}
	(*data)->paths = get_paths(envp);
	if (!(*data)->paths)
	{
		free((*data)->pid);
		free((*data));
		return ;
	}
}
