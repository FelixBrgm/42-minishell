/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 19:14:13 by fbruggem         ###   ########.fr       */
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
		if (cmd[j + 1])
			printf(" ");
		j++;
	}
	printf("\n");
	return (1);
}

int	builtin_echo_n(char **cmd, char ** env)
{	int i;
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
		if (cmd[j + 1])
			printf(" ");
		j++;
	}
	return (1);
}