/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/11 15:45:36 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"
void	setup_pipes_normal(int *fd_current0, int *fd_current1, int fd_temp, t_child *child);
void	setup_pipes_last(int fd_current0, t_child *child);

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
				append_int(pids, child_exec(global->children[i], global->env, fd_temp[0]));;
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
			append_int(pids, child_exec(global->children[i], global->env, -1));;
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
	if (i > 1022)
		return ;
	p[i] = n;
	p[i + 1] = -1;
}