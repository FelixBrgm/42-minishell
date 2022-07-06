/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:06:15 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 14:02:25 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int exit_code;

/**
 * @brief Executes a built in command
 * 
 * @param cmd The command like { "/bin/ls" , "params", ...} 
 * @param env environment from global
 * @return 0 when ok and 1 when error
 */
int	builtin_exec(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "echo" , ft_strlen(cmd[0])) == 0)
		return (builtin_echo(cmd));
	else if (ft_strncmp(cmd[0], "pwd" , ft_strlen(cmd[0])) == 0)
		return (builtin_pwd());
	else if (ft_strncmp(cmd[0], "export" , ft_strlen(cmd[0])) == 0)
		return (builtin_export(cmd, env));
	else if (ft_strncmp(cmd[0], "env" , ft_strlen(cmd[0])) == 0)
		return (builtin_env(env, cmd));
	else if (ft_strncmp(cmd[0], "cd" , ft_strlen(cmd[0])) == 0)
		return (builtin_cd(cmd, env));
	else if (ft_strncmp(cmd[0], "unset" , ft_strlen(cmd[0])) == 0)
		return (builtin_unset(cmd, env));
	else if (ft_strncmp(cmd[0], "exit" , ft_strlen(cmd[0])) == 0)
		return (builtin_exit(cmd));
	else 
		return (1);
}