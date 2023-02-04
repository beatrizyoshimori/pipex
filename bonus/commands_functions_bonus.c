/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_functions_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:20 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/04 14:04:24 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	delete_quotes(char **split_str)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	i = 0;
	while (split_str[i])
	{
		tmp = ft_strdup(split_str[i]);
		free(split_str[i]);
		split_str[i] = malloc(ft_strlen(tmp) - 1);
		j = 0;
		k = 0;
		while (tmp[j])
		{
			if (tmp[j] != '\'' && tmp[j] != '\"')
				split_str[i][k++] = tmp[j++];
			else
				j++;
		}
		split_str[i][k] = '\0';
		free(tmp);
		i++;
	}
}

char	**get_commands(char *str)
{
	int		i;
	int		num_single_quotes;
	char	**split_str;

	i = 0;
	num_single_quotes = 0;
	if (ft_strchr(str, '\'') != ft_strrchr(str, '\'')
		|| ft_strchr(str, '\"') != ft_strrchr(str, '\"'))
	{
		while (str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				num_single_quotes++;
			if (str[i] == ' ' && num_single_quotes % 2 == 0)
				str[i] = '\t';
			i++;
		}
		split_str = ft_split(str, '\t');
		delete_quotes(split_str);
	}
	else
		split_str = ft_split(str, ' ');
	return (split_str);
}
