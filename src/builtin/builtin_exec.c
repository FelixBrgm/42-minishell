/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:06:15 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/12 21:20:05 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Executes a built in command
 * 
 * @param child The child pointer with file descriptors 
 * @param env environment from global
 * @return 0 when ok and 1 when error
 */
int	builtin_exec(t_child *child, char **env)
{
	if (ft_strncmp(child->cmd[0], "echo", ft_strlen(child->cmd[0])) == 0)
		return (builtin_echo(child));
	else if (ft_strncmp(child->cmd[0], "pwd", ft_strlen(child->cmd[0])) == 0)
		return (builtin_pwd(child));
	else if (ft_strncmp(child->cmd[0], "export", ft_strlen(child->cmd[0])) == 0)
		return (builtin_export(child, env));
	else if (ft_strncmp(child->cmd[0], "env", ft_strlen(child->cmd[0])) == 0)
		return (builtin_env(env, child));
	else if (ft_strncmp(child->cmd[0], "cd", ft_strlen(child->cmd[0])) == 0)
		return (builtin_cd(child, env));
	else if (ft_strncmp(child->cmd[0], "unset", ft_strlen(child->cmd[0])) == 0)
		return (builtin_unset(child, env));
	else if (ft_strncmp(child->cmd[0], "exit", ft_strlen(child->cmd[0])) == 0)
		return (builtin_exit(child));
	else 
		return (1);
}