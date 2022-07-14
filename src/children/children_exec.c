/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/15 01:06:17 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int		open_tmp_read(void);

void	children_exec(t_global *global)
{
	int		fd_current[2];
	int		fd_temp[2];
	int		infd_tmp;
	int		outfd_tmp;
	t_child	*tmp;

	fd_current[0] = -1;
	fd_current[1] = -1;
	tmp = global->children_head;
	while (tmp != NULL)
	{
		if (tmp->limiter.lim != NULL)
			limiter_exec(tmp, global->env);
		else if (cmd_count(global) <= 1)
		{
			if (builtin_is_cmd(tmp->cmd, global->env))
			{
				infd_tmp = dup(STDIN_FILENO);
				outfd_tmp = dup(STDOUT_FILENO);
				if (tmp->fd_in != -1 && dup2_close(tmp->fd_in, STDIN_FILENO))
				{
					perror("Error fd_in");
					break ;
				}
				if (tmp->fd_out != -1 && dup2_close(tmp->fd_out, STDOUT_FILENO))
				{
					perror("Error fd_out");
					break ;
				}
				if (tmp->file_in && child_exec_set_file_in_fd(tmp->file_in))
				{
					perror("Error file_in");
					break ;
				}
				if (tmp->prev && tmp->prev->limiter.lim != NULL
					&& tmp->limiter.lim == NULL
					&& dup2_close(open_tmp_read(), STDIN_FILENO))
				{
					perror("Error here_doc");
					break ;
				}
				if (tmp->file_out_trunc
					&& child_exec_set_file_out_trunc_fd(tmp->file_out_trunc))
				{
					perror("Error file_out_trunc");
					break ;
				}
				if (tmp->file_out_app
					&& child_exec_set_file_out_app_fd(tmp->file_out_app))
				{
					perror("Error file_out_app");
					break ;
				}
				dup2(infd_tmp, STDIN_FILENO);
				builtin_exec(tmp, global->env);
				dup2_close(infd_tmp, STDIN_FILENO);
				dup2_close(outfd_tmp, STDOUT_FILENO);
			}
			else
			{
				setup_pipes_last(fd_current[0], tmp);
				global->this_pid
					= child_exec(tmp, global->env, -1, &global->this_pid);
				if (fd_current[0] != -1)
					close(fd_current[0]);
			}
		}
		if (tmp->limiter.lim == NULL
			&& tmp->next != NULL && cmd_count(global) > 1)
		{
			pipe(fd_temp);
			setup_pipes_normal(&fd_current[0], &fd_current[1], fd_temp[1], tmp);
			global->this_pid
				= child_exec(tmp, global->env, fd_temp[0], &global->this_pid);
			if (tmp->prev != NULL)
				close(fd_current[0]);
			fd_current[0] = fd_temp[0];
			close(fd_current[1]);
		}
		else if (cmd_count(global) > 1 && tmp->limiter.lim == NULL)
		{
			setup_pipes_last(fd_current[0], tmp);
			global->this_pid
				= child_exec(tmp, global->env, -1, &global->this_pid);
			if (fd_current[0] != -1)
				close(fd_current[0]);
		}
		tmp = tmp->next;
	}
	signal(SIGINT, SIG_IGN);
	while (wait(&exit_code) != -1 || errno != ECHILD)
		continue ;
}
