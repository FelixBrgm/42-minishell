/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:34:17 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 17:01:18 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int		child_exec_set_file_in_fd(char *file);
int		child_exec_set_file_out_trunc_fd(char *file);
int		child_exec_set_file_out_app_fd(char *file);
int		dup2_close(int fd, int fd2);
void	perror_exit(char *str);

void	child_exec(t_child *child, char **env)
{
	int	pid;

	pid = fork();
	if (pid != 0)
		return ;
	if (child->fd_in != -1 && !child->limiter && dup2_close(child->fd_in, STDIN_FILENO))
		perror_exit("Error fd_in");
	if (child->fd_out != -1 && dup2_close(child->fd_out, STDOUT_FILENO))
		perror_exit("Error fd_out");
	if (child->file_in && child_exec_set_file_in_fd(child->file_in))
		perror_exit("Error file_in");
	if (child->file_out_trunc && child_exec_set_file_out_trunc_fd(child->file_out_trunc))
		perror_exit("Error file_out_trunc");
	if (child->file_out_app && child_exec_set_file_out_app_fd(child->file_out_app))
		perror_exit("Error file_out_app");
	if (child->limiter)
		limiter_exec(child);
	else if(builtin_is_cmd(child->cmd, env) && builtin_exec(child->cmd, env))
		perror_exit("Error builtin_exec");
	else
	{
		child->cmd[0] = child_where(child->cmd[0], env);
		execve(child->cmd[0], child->cmd, env);
	}
	perror_exit("Error execve");
}

int	child_exec_set_file_in_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0 || dup2_close(fd, STDIN_FILENO))
		return(1);
	return (0);
}

int	child_exec_set_file_out_trunc_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0 || dup2_close(fd, STDOUT_FILENO))
		return (1);
	return (0);
}

int	child_exec_set_file_out_app_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	if (fd < 0 || dup2_close(fd, STDOUT_FILENO))
		return (1);
	return (0);
}

int	dup2_close(int fd, int fd2)
{
	if (dup2(fd, fd2) < 0 || close(fd) < 0)
		return (1);
	return (0);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(errno);
}