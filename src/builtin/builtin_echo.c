/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 19:10:48 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_echo(char **cmd, char ** env)
{
	int i;
	int	j;
	
	j = 1;
	
	while (cmd[j])
	{
		i = 0;
		while(cmd[j][i])
		{
			printf("%c", cmd[j][i]);
			i++;
		}
		j++;
	}
	
	return (1);
}

int	builtin_echo_n(char **cmd, char ** env)
{
	int i;
	int	j;
	
	j = 1;
	
	while (cmd[j])
	{
		i = 0;
		while(cmd[j][i])
		{
			if (!(cmd[j][i] == '\n' && cmd[j][i + 1] == '\0'))
				printf("%c", cmd[j][i]);
			i++;
		}
		j++;
	}
	
	return (1);
}