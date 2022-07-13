/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:57:45 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/12 21:31:55 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Mimics the functionality of env without params and options
 * 
 * @param env 
 * @return int 0 = ok | 1 = error
 */
int builtin_env(char **env, t_child *child)
{
	int	i;

	i = 0;
	if (close(STDIN_FILENO) < 0)
		return (1);
	if (!env)
		return (1);
	if (!child->cmd)
		return (1);
	if (child->cmd[1])
		return (1);
	while (env[i])
	{
		if (ft_strnstr(env[i], "=", ft_strlen(env[i])))
			printf("%s\n", env[i]);
		i++;
	}
	if (close(STDOUT_FILENO) < 0)
		return (1);
	return (0);
}
