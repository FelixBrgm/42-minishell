/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 20:40:38 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

void	children_exec(t_global *global)
{
	int	fd_current[2];
	int	fd_temp[2];
	int	i;
	int	ex_status;

	i = 0;
	fd_current[0] = -1;
	fd_current[1] = -1;
	while (global->children[i])
	{
		if (global->children[i + 1])
		{
			pipe(fd_temp);
			fd_current[1] = fd_temp[1];
			global->children[i]->fd_in = fd_current[0];
			global->children[i]->fd_out = fd_current[1];
			child_exec(global->children[i], global->env, &global->ex_status);
			if (i > 0)
				close(fd_current[0]);
			fd_current[0] = fd_temp[0];
			close(fd_current[1]);
		}
		else
		{
			global->children[i]->fd_in = fd_current[0];
			global->children[i]->fd_out = -1;
			child_exec(global->children[i], global->env, &ex_status);
			close(fd_current[0]);
		}
		i++;
	}
	if (WIFEXITED(ex_status))
		printf("EXIT CODE WAS %d\n", WEXITSTATUS(&global->ex_status));
}