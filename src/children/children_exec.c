/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/08 15:57:03 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

extern int exit_code;

static void append_int(int *p, int n);

void	children_exec(t_global *global)
{
	int	fd_current[2];
	int	fd_temp[2];
	int	i;
	int	pids[1024];

	i = 0;
	pids[0] = -1;
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
			append_int(pids, child_exec(global->children[i], global->env, fd_temp[0]));
			if (i > 0)
				close(fd_current[0]);
			fd_current[0] = fd_temp[0];
			close(fd_current[1]);
		}
		else
		{
			global->children[i]->fd_in = fd_current[0];
			global->children[i]->fd_out = -1;
			append_int(pids, child_exec(global->children[i], global->env, global->ex_status));
			if (i > 0)
				close(fd_current[0]);
		}
		i++;
	}
	i = 0;
	while (pids[i] != -1)
	{
		waitpid(pids[i], &exit_code, 0);
		i++;
	}
}

static void append_int(int *p, int n)
{
	int	i;

	i = 0;
	while (p[i] != -1)
		i++;
	if (i < 1022)
		return ;
	p[i] = n;
	p[i + 1] = -1;
}