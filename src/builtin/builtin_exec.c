/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:06:15 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 14:56:07 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_exec(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "echo" , 5) != 0)
		return (builtin_echo(cmd, env));
	if (ft_strncmp(cmd[0], "echo -n" , 8) != 0)
		return (builtin_echo_n(cmd, env));
	if (ft_strncmp(cmd[0], "pwd" , 4) != 0)
		return (builtin_pwd());
	if (ft_strncmp(cmd[0], "export" , 7) != 0)
		return (builtin_export(cmd, env));
	else 
		return (1);
}