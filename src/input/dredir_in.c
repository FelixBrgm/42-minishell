/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dredir_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:02:01 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/07 14:28:24 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*get_dredir(char *str)
{
	char	**tmp;
	int		size;
	char	*ret;

	tmp = split_mod(str, ' ');
	ret = NULL;
	if (is_dredir_in_split(tmp) > -1)
	{
		if (tmp[is_dredir_in_split(tmp) + 1] == NULL || !ft_strncmp(tmp[is_dredir_in_split(tmp) + 1], "\n", 2))
			return (NULL);
		ret = ft_strjoin_free(ft_strdup(tmp[is_dredir_in_split(tmp) + 1]), " <<");
	}
	free_split(tmp);
	return (ret);
}

char	*rem_dredir_in(char *str)
{
	char	**tmp;
	char	*ret;
	int		i;

	tmp = split_mod(str, ' ');
	i = 0;
	ret = NULL;
	while (tmp != NULL && tmp[i] != NULL)
	{
		if (is_dredir_in(tmp[i]) == -1)
		{
			ret = ft_strjoin_free(ret, tmp[i]);
			ret = ft_strjoin_free(ret, " ");
		}
		else
			i++;
		i++;
	}
	if (tmp != NULL)
		free_split(tmp);
	if (str != NULL)
		free(str);
	return (ret);
}

char **sep_dredir_in(int count, char **old_input)
{
	char	**ret;
	int		i;
	int		j;

	ret = malloc((count + 1) * sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (old_input[j] != NULL)
	{
		if (is_dredir_in(old_input[j]) > -1)
		{
			ret[i] = get_dredir(old_input[j]);
			if (ret[i] == NULL)
				return (NULL);
			old_input[j] = rem_dredir_in(old_input[j]);
			// ret[++i] = ft_strdup(old_input[j]);
			i++;
		}
		ret[i++] = ft_strdup(old_input[j++]);
	}
	free_split(old_input);
	ret[i] = NULL;
	return (ret);
}

int	is_dredir_in_split(char **str)
{
	int	i;

	i = split_len(str) - 1;
	while (i >= 0)
	{
		if (ft_strlen(str[i]) == 2 && str[i][0] == '<' && str[i][1] == '<')
			return (i);
		i--;
	}
	return (-1);
}

int	is_dredir_in(char *str)
{
	int	i;
	int	j;
	char	**tmp;

	tmp = split_mod(str, ' ');
	j = split_len(tmp) - 1;
	while (j >= 0)
	{
		i = 0;
		while (tmp[j][i] != '\0')
		{
			if (ft_strlen(tmp[j]) == 2 && tmp[j][i] == '<' && tmp[j][i + 1] == '<')
			{
				free_split(tmp);
				return (j);
			}
			i++;
		}
		j--;
	}
	free_split(tmp);
	return (-1);
}