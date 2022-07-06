/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_is_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:01 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 13:34:57 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int exit_code;

int	builtin_is_cmd(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "echo" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "pwd" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "export" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "env" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "cd" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "unset" , ft_strlen(cmd[0])) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "exit" , ft_strlen(cmd[0])) == 0)
		return (1);
	return (0);
}