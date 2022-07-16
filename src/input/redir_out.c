/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_out.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:18:31 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/16 20:29:29 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	is_redir_out(char *str)
{
	if (ft_strlen(str) == 1 && str[0] == '>')
		return (1);
	return (-1);
}

char	*rem_redir_out(char *str)
{
	char	**tmp;
	char	*ret;
	int		i;

	tmp = split_mod(str, ' ');
	i = 0;
	ret = NULL;
	while (tmp != NULL && tmp[i] != NULL)
	{
		if (is_redir_out(tmp[i]) == -1)
		{
			ret = ft_strjoin_free(ret, tmp[i]);
			ret = ft_strjoin_free(ret, " ");
		}
		else
			i++;
		i++;
	}
	ft_free_split(tmp);
	if (str != NULL)
		free(str);
	return (ret);
}

int	is_redir_out_split(char **str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != NULL)
	{
		if (ft_strlen(str[i]) == 1 && str[i][0] == '>')
			return (i);
		i++;
	}
	return (-1);
}
