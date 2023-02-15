/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_functions_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byoshimo <byoshimo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 19:50:20 by byoshimo          #+#    #+#             */
/*   Updated: 2023/02/15 19:37:57 by byoshimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*remove_quotes(char *dst, char *src)
{
	int	j;
	int	k;

	j = 0;
	k = 0;
	while (src[j])
	{
		if (src[j] != '\'' && src[j] != '\"')
			dst[k++] = src[j++];
		else
			j++;
	}
	dst[k] = '\0';
	return (dst);
}

void	check_quotes(char **split_str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (split_str[i])
	{
		if (ft_strchr(split_str[i], '\'') != ft_strrchr(split_str[i], '\'')
			|| ft_strchr(split_str[i], '\"') != ft_strrchr(split_str[i], '\"'))
		{
			tmp = ft_strdup(split_str[i]);
			free(split_str[i]);
			split_str[i] = malloc(ft_strlen(tmp) - 1);
			split_str[i] = remove_quotes(split_str[i], tmp);
			free(tmp);
		}
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
		check_quotes(split_str);
	}
	else
		split_str = ft_split(str, ' ');
	return (split_str);
}
