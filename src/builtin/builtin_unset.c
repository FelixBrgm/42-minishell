/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 15:30:30 by fbruggem         ###   ########.fr       */
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
int	builtin_unset(char **cmd, char **env)
{
	int	i;
	int	c;

	char **temp;
	if (!cmd)
		return (1);
	c = 1;
	while (cmd[c])
	{
		i = 1;
		temp = env_get(env, cmd[c]);
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