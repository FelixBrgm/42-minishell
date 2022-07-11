/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dredir_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:02:01 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/08 20:49:48 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

// char	*get_dredir(char *str)
// {
// 	char	**tmp;
// 	int		size;
// 	char	*ret;

// 	tmp = split_mod(str, ' ');
// 	ret = NULL;
// 	if (is_dredir_in_split(tmp) > -1)
// 	{
// 		if (tmp[is_dredir_in_split(tmp) + 1] == NULL || !ft_strncmp(tmp[is_dredir_in_split(tmp) + 1], "\n", 2))
// 			return (NULL);
// 		ret = ft_strjoin_free(ft_strdup(tmp[is_dredir_in_split(tmp) + 1]), " <<");
// 	}
// 	free_split(tmp);
// 	return (ret);
// }

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

int	is_dredir_in_split(char **str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != NULL)
	{
		if (ft_strlen(str[i]) == 2 && str[i][0] == '<' && str[i][1] == '<')
			return (i);
		i++;
	}
	return (-1);
}

int	is_dredir_in(char *str)
{

	if (ft_strlen(str) == 2 && str[0] == '<' && str[1] == '<')
		return (1);
	return (-1);
}