/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:26:52 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 12:42:31 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"
void	setup_pipes_normal(int *fd_current0, int *fd_current1, int fd_temp, t_child *child);
void	setup_pipes_last(int fd_current0, t_child *child);
int		cmd_count(t_global *global);
int		dup2_close(int fd, int fd2);
int		child_exec_set_file_in_fd(char *file);
int		child_exec_set_file_out_trunc_fd(char *file);
int		child_exec_set_file_out_app_fd(char *file);

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
		{
			// fprintf(stderr, "limiter\n");
			limiter_exec(tmp, global->env);
		}
		else if (cmd_count(global) <= 1)
		{
			if (builtin_is_cmd(tmp->cmd, global->env))
			{
				if (tmp->fd_in != -1 && dup2_close(tmp->fd_in, STDIN_FILENO))
					perror_exit("Error fd_in");
				if (tmp->fd_out != -1 && dup2_close(tmp->fd_out, STDOUT_FILENO))
					perror_exit("Error fd_out");
				if (tmp->file_in && child_exec_set_file_in_fd(tmp->file_in))
					perror_exit("Error file_in");
				if (tmp->prev && tmp->prev->limiter.lim != NULL && tmp->limiter.lim == NULL && dup2_close(open_tmp_read(), STDIN_FILENO))
					perror_exit("Error here_doc");
				if (tmp->file_out_trunc && child_exec_set_file_out_trunc_fd(tmp->file_out_trunc))
					perror_exit("Error file_out_trunc");
				if (tmp->file_out_app && child_exec_set_file_out_app_fd(tmp->file_out_app))
					perror_exit("Error file_out_app");
				infd_tmp = dup(STDIN_FILENO);
				outfd_tmp = dup(STDOUT_FILENO);
				builtin_exec(tmp, global->env);
				dup2_close(infd_tmp, STDIN_FILENO);
				dup2_close(outfd_tmp, STDOUT_FILENO);
			}
			else
			{
				setup_pipes_last(fd_current[0], tmp);
				global->this_pid = child_exec(tmp, global->env, -1, &global->this_pid);
				if (fd_current[0] != -1)
					close(fd_current[0]);
			}
		}
		if (tmp->limiter.lim == NULL && tmp->next != NULL && cmd_count(global) > 1)
		{
			pipe(fd_temp);
			setup_pipes_normal(&fd_current[0], &fd_current[1], fd_temp[1], tmp);
			// fprintf(stderr, "child-mid\n");
			global->this_pid = child_exec(tmp, global->env, fd_temp[0], &global->this_pid);
			if (tmp->prev != NULL)
				close(fd_current[0]);
			fd_current[0] = fd_temp[0];
			close(fd_current[1]);
		}
		else if (cmd_count(global) > 1 && tmp->limiter.lim == NULL)
		{
			setup_pipes_last(fd_current[0], tmp);
			global->this_pid = child_exec(tmp, global->env, -1, &global->this_pid);
			if (fd_current[0] != -1)
				close(fd_current[0]);
		}
		tmp = tmp->next;
	}
	while (wait(&exit_code) != -1 || errno != ECHILD)
        continue ;
}

int	cmd_count(t_global *global)
{
	int	count;
	t_child *tmp;

	count = 0;
	tmp = global->children_head;
	while (tmp != NULL)
	{
		if (tmp->cmd != NULL && tmp->limiter.lim == NULL)
			count++;
		tmp = tmp->next;
	}
	return (count);
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
