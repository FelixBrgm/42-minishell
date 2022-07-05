/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:06:15 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 13:57:36 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Executes a built in command
 * 
 * @param cmd The command like { "/bin/ls" , "params", ...} 
 * @param env environment from global
 * @return 0 when ok and 1 when error
 */
int	builtin_exec(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "echo -n" , ft_strlen(cmd[0])) == 0)
		return (builtin_echo_n(cmd));
	else if (ft_strncmp(cmd[0], "echo" , ft_strlen(cmd[0])) == 0)
		return (builtin_echo(cmd));
	else if (ft_strncmp(cmd[0], "pwd" , ft_strlen(cmd[0])) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd[0], "export" , ft_strlen(cmd[0])) == 0)
		return (builtin_export(cmd, env));
	else if (ft_strncmp(cmd[0], "env" , ft_strlen(cmd[0])) == 0)
	return (builtin_env(env));
	else 
		return (1);
}