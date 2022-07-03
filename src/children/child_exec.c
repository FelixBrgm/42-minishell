/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:34:17 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 16:02:02 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int	child_exec_set_file_in_fd(char *file);
int	child_exec_set_file_out_fd(char *file);


int	child_exec(t_child *child, char **env)
{
	int	pid;

	pid = fork();
	if (pid != 0)
		return (0);
	if (child->fd_in != -1)
		dup2(child->fd_in, STDIN_FILENO);
	if (child->fd_out != -1)
		dup2(child->fd_out, STDOUT_FILENO);
	if (child->file_in)
		child_exec_set_file_in_fd(child->file_in);
	if (child->file_out)
		child_exec_set_file_out_fd(child->file_out);
	if (child->limiter)
		limiter_exec(child);
	else
		execve(child->cmd[0], child->cmd, env);
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

int	child_exec_set_file_out_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_CREAT, S_IRUSR | S_IWUSR);
	dup2(fd, STDOUT_FILENO);
	return (0);
}