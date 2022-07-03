/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 16:01:32 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

void	children_exec(t_global *global)
{
	int	fd_current[2];
	int	fd_temp[2];
	int	i;

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
			child_exec(global->children[i], global->env);
			fd_current[0] = fd_temp[0];
		}
		else
		{
			global->children[i]->fd_in = fd_current[0];
			global->children[i]->fd_out = -1;
			child_exec(global->children[i], global->env);
		}
		i++;
	}
	
}