/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_is_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:01 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/14 13:45:43 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_is_cmd(char **cmd, char **env)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd[0], "echo", ft_strlen("echo")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "pwd", ft_strlen("pwd")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "export", ft_strlen("export")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "env", ft_strlen("env") == 0))
		return (1);
	if (ft_strncmp(cmd[0], "cd", ft_strlen("cd")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "unset", ft_strlen("unset")) == 0)
		return (1);
	if (ft_strncmp(cmd[0], "exit", ft_strlen("exit")) == 0)
		return (1);
	return (0);
}
