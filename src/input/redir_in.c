/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:18:45 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/04 19:23:51 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_redir_in(char *str)
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
			if (ft_strlen(tmp[j]) == 1 && tmp[j][i] == '<')
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

char	*rem_redir_in(char *str)
{
	char	**tmp;
	char	*ret;
	int		i;

	tmp = split_mod(str, ' ');
	i = 0;
	ret = NULL;
	while (tmp[i] != NULL)
	{
		if (is_redir_in(tmp[i]) == -1)
		{
			ret = ft_strjoin_free(ret, tmp[i]);
			ret = ft_strjoin_free(ret, " ");
		}
		else
			i++;
		i++;
	}
	free_split(tmp);
	free(str);
	return (ret);
}
