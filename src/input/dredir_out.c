/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dredir_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:16:40 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/06 14:01:28 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_dredir_out(char *str)
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
			if (ft_strlen(tmp[j]) == 2 && tmp[j][i] == '>' && tmp[j][i + 1] == '>')
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

char	*rem_dredir_out(char *str)
{
	char	**tmp;
	char	*ret;
	int		i;

	tmp = split_mod(str, ' ');
	i = 0;
	ret = NULL;
	while (tmp != NULL && tmp[i] != NULL)
	{
		if (is_dredir_out(tmp[i]) == -1)
		{
			ret = ft_strjoin_free(ret, tmp[i]);
			ret = ft_strjoin_free(ret, " ");
		}
		else
			i++;
		i++;
	}
	free_split(tmp);
	if (str != NULL)
		free(str);
	return (ret);
}
