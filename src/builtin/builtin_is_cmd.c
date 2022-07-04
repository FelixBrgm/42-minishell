/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_is_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:34:01 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 14:56:35 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_is_cmd(char **cmd, char **env)
{
	if (ft_strncmp(cmd[0], "echo" , 5) != 0)
		return (1);
	if (ft_strncmp(cmd[0], "echo -n" , 8) != 0)
		return (1);
	if (ft_strncmp(cmd[0], "pwd" , 4) != 0)
		return (1);
	if (ft_strncmp(cmd[0], "export" , 7) != 0)
		return (1);
	return (0);
}