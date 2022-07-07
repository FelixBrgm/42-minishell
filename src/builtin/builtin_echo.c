/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/08 01:42:32 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


/**
 * @brief Prints the given parameters already extended with env
 * 
 * @param cmd as {"echo", "VALUE", ... }
 * @return int 0 
 */
int	builtin_echo(char **cmd)
{
	int i;
	int	j;
	int	n;
	
	n = 0;
	j = 1;
	if (!cmd)
		return (1);
	while (cmd[j] && ft_strncmp(cmd[j], "-n", 3) == 0)
	{
		n = i;
		j++;
	}
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
	if (n == 0)
		printf("\n");
	return (0);
}