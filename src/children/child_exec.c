/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:34:17 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/14 14:20:39 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int		child_exec_set_file_in_fd(char *file);
int		child_exec_set_file_out_trunc_fd(char *file);
int		child_exec_set_file_out_app_fd(char *file);
int		dup2_close(int fd, int fd2);
void	perror_exit(char *str);
int		child_need_fork(char **cmd);
int		open_tmp_read(void);

//fix not forking when input command was "$"

int	child_exec(t_child *child, char **env, int free_pipe, int *this_pid)
{
	int		pid;
	char	*path;

	pid = 0;
	// if (child_need_fork(child->cmd))
	pid = fork();
	if (pid != 0)
		return (pid);
	*this_pid = pid;
	if (free_pipe != -1)
		close(free_pipe);
	if (child->fd_in != -1 && dup2_close(child->fd_in, STDIN_FILENO))
		perror_exit("Error fd_in");
	if (child->fd_out != -1 && dup2_close(child->fd_out, STDOUT_FILENO))
		perror_exit("Error fd_out");
	if (child->file_in && child_exec_set_file_in_fd(child->file_in))
		perror_exit("Error file_in");
	if (child->prev && child->prev->limiter.lim != NULL && child->limiter.lim == NULL && dup2_close(open_tmp_read(), STDIN_FILENO))
		perror_exit("Error here_doc");
	if (child->file_out_trunc && child_exec_set_file_out_trunc_fd(child->file_out_trunc))
		perror_exit("Error file_out_trunc after fork");
	if (child->file_out_app && child_exec_set_file_out_app_fd(child->file_out_app))
		perror_exit("Error file_out_app");
	if(builtin_is_cmd(child->cmd, env))
	{
		if (builtin_exec(child, env))
		{
			printf("Error builtin_exec\n");
			// if (child_need_fork(child->cmd))
			exit(1);
		}
		// if (child_need_fork(child->cmd))
		exit(0);
	}
	else
	{
		// fprintf(stderr, "before %s\n", child->cmd[0]);
		if (child->cmd)
			path = child_where(child->cmd[0], env);
		else
			path = NULL;
		// fprintf(stderr, "%s\n", path);
		// sleep(100);
		execve(path, child->cmd, env);
	}
	perror_exit("Error execve");
	return(0);
}

int	child_exec_set_file_in_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		fprintf(stderr, "open failed: file name %s\n", file);
		return(1);
	}

	if (dup2_close(fd, STDIN_FILENO) < 0)
	{
		fprintf(stderr, "dup2 in file in failed\n");
		return (1);
	}
	return (0);
}

int	child_exec_set_file_out_trunc_fd(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0 || dup2_close(fd, STDOUT_FILENO))
		return (1);
	return (0);
}

int	child_exec_set_file_out_app_fd(char *file)
{
	int	fd;
	
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0 || dup2_close(fd, STDOUT_FILENO))
		return (1);
	return (0);
}

int	dup2_close(int fd, int fd2)
{
	if (dup2(fd, fd2) < 0)
		return (1);
	if (close(fd) < 0)
		return (1);
	return (0);
}

void	perror_exit(char *str)
{
	perror(str);
	exit(1);
}

int	child_need_fork(char **cmd)
{
	if (cmd == NULL)
		return (1);
	if (ft_strncmp(cmd[0], "export" , ft_strlen(cmd[0])) == 0 
		&& cmd[1])
		return (0);
	if (ft_strncmp(cmd[0], "unset" , ft_strlen(cmd[0])) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "cd" , ft_strlen(cmd[0])) == 0)
		return (0);
	if (ft_strncmp(cmd[0], "exit" , ft_strlen(cmd[0])) == 0)
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