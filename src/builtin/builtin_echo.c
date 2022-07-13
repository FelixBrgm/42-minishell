/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:08:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/12 21:30:26 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief Prints the given parameters already extended with env
 * 
 * @param cmd as {"echo", "VALUE", ... }
 * @return int 0 
 */
int	builtin_echo(t_child *child)
{
	int i;
	int	j;
	int	n;
	
	n = 0;
	j = 1;
	if (close(STDIN_FILENO) < 0)
		return (1);
	if (!child->cmd)
		return (1);
	while (child->cmd[j] && ft_strncmp(child->cmd[j], "-n", 3) == 0)
	{
		n = i;
		j++;
	}
	while (child->cmd[j])
	{
		i = 0;
		while(child->cmd[j][i])
		{
			printf("%c", child->cmd[j][i]);
			i++;
		}
		if (child->cmd[j + 1])
			printf(" ");
		j++;
	}
	if (n == 0)
		printf("\n");
	if (close(STDOUT_FILENO) < 0)
		return (1);
	return (0);
}
