/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:34:17 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 15:26:50 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int	child_exec_set_file_in_fd(char *file);
int	child_exec_set_file_out_trunc_fd(char *file);
int	child_exec_set_file_out_app_fd(char *file);

int	child_exec(t_child *child, char **env)
{
	int	pid;

	pid = fork();
	if (pid != 0)
		return (0);
	if (child->fd_in != -1 && !child->limiter)
		dup2(child->fd_in, STDIN_FILENO);
	if (child->fd_out != -1)
		dup2(child->fd_out, STDOUT_FILENO);
	if (child->file_in)
		child_exec_set_file_in_fd(child->file_in);
	if (child->file_out_trunc)
		child_exec_set_file_out_trunc_fd(child->file_out_trunc);
	if (child->file_out_app)
		child_exec_set_file_out_app_fd(child->file_out_app);
	if (child->limiter)
		limiter_exec(child);
	else if(builtin_is_cmd(child->cmd, env))
		builtin_exec(child->cmd, env);
	else
	{
		child->cmd[0] = child_where(child->cmd[0], env);
		execve(child->cmd[0], child->cmd, env);
	}
	exit(1);
}

int	child_exec_set_file_in_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return(1);
	// PRINT OUT ERROR MESSAGE
	dup2(fd, STDIN_FILENO);
	return (0);
}

int	child_exec_set_file_out_trunc_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	return (0);
}

int	child_exec_set_file_out_app_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	return (0);
}