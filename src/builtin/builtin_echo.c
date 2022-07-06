/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 13:38:11 by fbruggem         ###   ########.fr       */
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
	while (cmd[j])
	{
		if (ft_strncmp(cmd[j], "-n", 3) == 0)
		{
			n = 1;
			j++;
		}
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