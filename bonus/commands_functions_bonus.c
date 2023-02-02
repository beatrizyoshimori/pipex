/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_functions_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:20 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/01 21:21:37 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	delete_single_quotes(char **split_str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_str[i])
	{
		if ((split_str[i][0] == '\'' || split_str[i][0] == '\"') && ft_strlen(split_str[i]) != 1)
		{
			tmp = ft_strdup(split_str[i]);
			free(split_str[i]);
			split_str[i] = malloc(ft_strlen(tmp) - 1);
			ft_strlcpy(split_str[i], (tmp + 1), ft_strlen(tmp) - 1);
			free(tmp);
		}
		else if ((ft_strchr(split_str[i], '\'') && ft_strchr(split_str[i], '\'') != ft_strrchr(split_str[i], '\''))
			|| (ft_strchr(split_str[i], '\"') && ft_strchr(split_str[i], '\"') != ft_strrchr(split_str[i], '\"')))
		{
			tmp = ft_strdup(split_str[i]);
			free(split_str[i]);
			split_str[i] = malloc(ft_strlen(tmp) - 1);
			int j = 0;
			int k = 0;
			while (tmp[j])
			{
				if (tmp[j] != '\'' && tmp[j] != '\"')
					split_str[i][k++] = tmp[j++];
				else
					j++;
			}
			split_str[i][k] = '\0';
		}
		i++;
	}
}

char	**get_commands(char *str)
{
	int		i;
	int		num_single_quotes;
	char	*tmp;
	char	**split_str;

	tmp = ft_strdup(str);
	i = 0;
	num_single_quotes = 0;
	if ((ft_strchr(str, '\'') && ft_strchr(str, '\'') != ft_strrchr(str, '\''))
		|| (ft_strchr(str, '\"') && ft_strchr(str, '\"') != ft_strrchr(str, '\"')))
	{
		while (tmp[i])
		{
			if (tmp[i] == '\'' || tmp[i] == '\"')
				num_single_quotes++;
			if (tmp[i] == ' ' && num_single_quotes % 2 == 0)
				tmp[i] = '\t';
			i++;
		}
		split_str = ft_split(tmp, '\t');
	}
	else
		split_str = ft_split(tmp, ' ');
	delete_single_quotes(split_str);
	free(tmp);
	return (split_str);
}
