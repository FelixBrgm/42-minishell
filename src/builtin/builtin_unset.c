/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/12 21:32:57 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


/**
 * @brief Unset a env variable
 * 
 * @param cmd 
 * @param env 
 * @return int 
 */
int	builtin_unset(t_child *child, char **env)
{
	int	i;
	int	c;

	if (close(STDIN_FILENO) < 0 && close(STDOUT_FILENO) < 0)
		return (1);
	char **temp;
	if (!child->cmd)
		return (1);
	c = 1;
	while (child->cmd[c])
	{
		i = 1;
		temp = env_get(env, child->cmd[c]);
		free(*temp);
		while(temp[i])
		{
			temp[i -1] = temp[i];
			i++;
		}
		temp[i -1] = NULL;
		c++;
	}
	return (0);
}
