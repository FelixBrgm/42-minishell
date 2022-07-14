/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:34:17 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/15 00:43:55 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int		child_need_fork(char **cmd);
int		open_tmp_read(void);
void	child_exec_builtin(char **env, t_child *child);
void	child_exec_error_handling(t_child *child);

int	child_exec(t_child *child, char **env, int free_pipe, int *this_pid)
{
	int		pid;
	char	*path;

	pid = 0;
	pid = fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	*this_pid = pid;
	if (free_pipe != -1)
		close(free_pipe);
	child_exec_error_handling(child);
	if (builtin_is_cmd(child->cmd, env))
		child_exec_builtin(env, child);
	else
	{
		if (child->cmd)
			path = child_where(child->cmd[0], env);
		else
			path = NULL;
		execve(path, child->cmd, env);
	}
	perror_exit("Error execve");
	return (0);
}

void	child_exec_error_handling(t_child *child)
{
	if (child->fd_in != -1 && dup2_close(child->fd_in, STDIN_FILENO))
		perror_exit("Error fd_in");
	if (child->fd_out != -1 && dup2_close(child->fd_out, STDOUT_FILENO))
		perror_exit("Error fd_out");
	if (child->file_in && child_exec_set_file_in_fd(child->file_in))
		perror_exit("Error file_in");
	if (child->prev && child->prev->limiter.lim != NULL
		&& child->limiter.lim == NULL
		&& dup2_close(open_tmp_read(), STDIN_FILENO))
		perror_exit("Error here_doc");
	if (child->file_out_trunc
		&& child_exec_set_file_out_trunc_fd(child->file_out_trunc))
		perror_exit("Error file_out_trunc after fork");
	if (child->file_out_app
		&& child_exec_set_file_out_app_fd(child->file_out_app))
		perror_exit("Error file_out_app");
}

int	child_need_fork(char **cmd)
{
	if (cmd == NULL)
		return (1);
	if (ft_strncmp(cmd[0], "export", ft_strlen(cmd[0])) == 0
		&& cmd[1])
		return (0);
	if (ft_strncmp(cmd[0], "unset", ft_strlen(cmd[0])) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "cd", ft_strlen(cmd[0])) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "exit", ft_strlen(cmd[0])) == 0)
		return (0);
	return (1);
}

int	open_tmp_read(void)
{
	int	fd;

	fd = open("./.tmp_minishell", O_RDONLY);
	if (fd < 0)
		return (-1);
	return (fd);
}

void	child_exec_builtin(char **env, t_child *child)
{
	if (!env || !child)
		exit(1);
	if (builtin_exec(child, env))
	{
		printf("Error builtin_exec\n");
		exit(1);
	}
	exit(0);
}
