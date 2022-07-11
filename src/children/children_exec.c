/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/10 11:25:45 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"
void	setup_pipes_normal(int *fd_current0, int *fd_current1, int fd_temp, t_child *child);
void	setup_pipes_last(int fd_current0, t_child *child);

void	children_exec(t_global *global)
{
	// int		i;
	t_child	*tmp;
	int		fd_temp[2];
	int		fd_current[2];

	// i = 0;
	fd_current[0] = -1;
	fd_current[1] = -1;
	tmp = global->children_head;
	while (tmp != NULL)
	{
		if (tmp->next != NULL)
		{
			if (tmp->limiter.lim != NULL)
			{
				// fprintf(stderr, "limiter\n");
				limiter_exec(tmp, global->env);
			}
			else
			{
				pipe(fd_temp);
				fd_current[1] = fd_temp[1];
				tmp->fd_in = fd_current[0];
				tmp->fd_out = fd_current[1];
				// global->children[i]->fd_in = fd_current[0];
				// global->children[i]->fd_out = fd_current[1];
				// setup_pipes_normal(&fd_current[0], &fd_current[1], fd_temp[1], tmp);
				// fprintf(stderr, "child-mid\n");
				child_exec(tmp, global->env, fd_temp[0]);
				if (tmp->prev != NULL)
					close(fd_current[0]);
				fd_current[0] = fd_temp[0];
				close(fd_current[1]);
			}
		}
		else
		{
			// setup_pipes_last(fd_current[0], tmp);
			tmp->fd_in = fd_current[0];
			tmp->fd_out = -1;
			// global->children[i]->fd_in = fd_current[0];
			// global->children[i]->fd_out = -1;
			// fprintf(stderr, "child-last\n");
			child_exec(tmp, global->env, -1);
			if (fd_current[0] != -1)
				close(fd_current[0]);
		}
		// i++;
		tmp = tmp->next;
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		continue ;
}

void	setup_pipes_normal(int *fd_current0, int *fd_current1, int fd_temp, t_child *child)
{
	*fd_current1 = fd_temp;
	child->fd_in = *fd_current0;
	child->fd_out = *fd_current1;
}

void	setup_pipes_last(int fd_current0, t_child *child)
{
	child->fd_in = fd_current0;
	child->fd_out = -1;
}