/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 13:57:45 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 14:02:01 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
/**
 * @brief Mimics the functionality of env without params and options
 * 
 * @param env 
 * @return int 0 = ok | 1 = error
 */
int builtin_env(char **env, char **cmd)
{
	int	i;

	i = 0;
	if (!env)
		return (1);
	if (!cmd)
		return (1);
	if (cmd[1])
		return (1);
	while (env[i])
	{
		if (ft_strnstr(env[i], "=", ft_strlen(env[i])))
			printf("%s\n", env[i]);
		i++;
	}
	return (0);
}