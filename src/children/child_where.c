/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_where.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:44:43 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/07 20:33:58 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

char	**where_get_paths(char **env);

char	*child_where( char *cmd,char **env)
{
	int		i;
	char	**paths;
	char	*res;
	char	*temp;

	paths = where_get_paths(env);
	i = 0;
	if (!paths && ft_strchr(cmd, '/'))
		return (cmd);
	if (!paths)
		return (ft_strjoin("./", cmd));
	while (paths && paths[i])
	{
		temp = paths[i];
		temp = ft_strjoin(temp, "/");
		res = ft_strjoin(temp, cmd);
		if (ft_strchr(cmd, '/') != 0)
			res = ft_strdup(cmd);
		if (access(res, 0) == 0)
		{
			i = 0;
			ft_free_split(paths);
			return (res);
		}
		free(res);
		i++;
	}
	ft_free_split(paths);
	return (NULL);
}

char	**where_get_paths(char **env)
{
	int		i;
	char	**paths;

	i = 0;
	while (env[i] && ft_strncmp("PATH", env[i], 4))
		i++;
	if (!env[i])
		return (NULL);
	paths = ft_split(&env[i][5], ':');
	return (paths);
}
