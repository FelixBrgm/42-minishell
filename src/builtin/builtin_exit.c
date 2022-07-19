/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/19 15:20:42 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int		is_only_digits(char *str);
int		setup_pipes_exit(t_child *child);
void	helper(t_global *global, t_child *child);

/**
 * @brief Cd's into the given directory
 * 
 * @param cmd as { "cd", "DIR" }
 * @return int 
 */
int	builtin_exit(t_child *child, t_global *global)
{
	close(STDIN_FILENO);
	if (!child->cmd)
		return (1);
	if (!child->cmd[1])
	{
		printf("exit\n");
		global_free(global);
		close(STDOUT_FILENO);
		exit(g_exit_code % 256);
	}
	else if (ft_2ptrlen((void **)child->cmd) == 2)
		helper(global, child);
	else
		printf("exit\nexit: too many arguments\n");
	close(STDOUT_FILENO);
	return (1);
}

void	helper(t_global *global, t_child *child)
{
	printf("exit\n");
	if (is_only_digits(child->cmd[1]))
	{
		printf("bash: exit: a: numeric argument required\n");
		exit(255);
	}
	close(STDOUT_FILENO);
	global_free(global);
	exit((unsigned int)ft_atoi(child->cmd[1]) % 256);
}

int	is_only_digits(char *str)
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
