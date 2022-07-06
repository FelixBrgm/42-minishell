/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 21:41:01 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

extern int exit_code;
int is_only_digits(char *str);

/**
 * @brief Cd's into the given directory
 * 
 * @param cmd as { "cd", "DIR" }
 * @return int 
 */
int	builtin_exit(char **cmd)
{
	if (!cmd)
		return (1);
	if (!cmd[1])
	{
		printf("exit\n");
		exit(exit_code % 256);
	}
	else if (ft_2ptrlen(cmd) == 2)
	{
		printf("exit\n");
		if (is_only_digits(cmd[1]))
			printf("bash: exit: a: numeric argument required\n");
		exit((unsigned int)ft_atoi(cmd[1]) % 256);
	}
	else
		printf("exit\nexit: too many arguments\n");
	return (0);
}

int is_only_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}



// int convert_to_exit(int n)
// {
	
// 	if (n < 0)
// }