/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 13:28:39 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Cd's into the given directory
 * 
 * @param cmd as { "cd", "DIR" }
 * @return int 
 */
int	builtin_cd(char **cmd, char **env)
{
	char temp[PATH_MAX];

	if (!cmd)
		return (1);
	if (!cmd[1])
		return (1);
	if (chdir(cmd[1]))
	{
		printf("cd: %s", cmd[1]);
		perror(NULL);
		return (1);
	}
	getcwd(temp, PATH_MAX);
	env_update(env, "PWD", temp);
	return (0);
}