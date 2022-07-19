/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:36:11 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/19 16:15:12 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

char	*set_vars(char *str, char **env);
int		open_tmp(void);

int	limiter_exec(t_child *child, char **env)
{
	char	*res;
	char	*tmp2;
	char	*read_line;
	int		fd;

	read_line = readline("here_doc> ");
	res = NULL;
	while (read_line && ft_strncmp(read_line, child->limiter.lim,
			ft_strlen(child->limiter.lim) + 1) != 0)
	{
		if (child->limiter.expand == 1)
		{
			tmp2 = read_line;
			read_line = set_vars(read_line, env);
			free(tmp2);
		}
		read_line = ft_strjoin_free(read_line, "\n");
		res = ft_strjoin_free(res, read_line);
		free(read_line);
		read_line = readline("here_doc> ");
	}
	fd = open_tmp();
	ft_putstr_fd(res, fd);
	close(fd);
	ft_protect(3, read_line, res, NULL);
	return (0);
}

int	open_tmp(void)
{
	int	fd;

	fd = open("./.tmp_minishell", O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (fd < 0)
		return (-1);
	return (fd);
}
