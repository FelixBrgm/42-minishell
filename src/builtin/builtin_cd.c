/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 12:35:12 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Cd's into the given directory
 * 
 * @param cmd as { "cd", "DIR" }
 * @return int 
 */
int	builtin_cd(t_child *child, char **env)
{
	char temp[PATH_MAX];

	if (close(STDIN_FILENO) < 0 && close(STDOUT_FILENO) < 0)
		return (1);
	if (!child->cmd)
		return (1);
	if (!child->cmd[1])
		return (0);
	getcwd(temp, PATH_MAX);	
	env_update(env, "OLDPWD", temp, 0);
	if (chdir(child->cmd[1]))
	{
		printf("cd: %s\n", child->cmd[1]);
		perror(NULL);
		return (1);
	}
	getcwd(temp, PATH_MAX);
	env_update(env, "PWD", temp, 0);
	return (0);
}
