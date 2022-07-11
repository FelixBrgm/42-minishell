/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_where.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 11:44:43 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/10 09:37:31 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

char	**where_get_paths(char **env);
void	print_split(char **str);

// char	*child_where( char *cmd,char **env)
// {
// 	int		i;
// 	char	**paths;
// 	char	*res;
// 	char	*temp;

// 	paths = where_get_paths(env);
// 	i = 0;
// 	if (!paths)
// 		return (ft_strjoin("./", cmd));
// 	while (paths && paths[i])
// 	{
// 		temp = paths[i];
// 		temp = ft_strjoin(temp, "/");
// 		res = ft_strjoin(temp, cmd);
// 		if (ft_strchr(cmd, '/') != 0)
// 			res = ft_strdup(cmd);
// 		fprintf(stderr, "res = %s\n", res);
// 		if (access(res, X_OK) == 0)
// 		{
// 			i = 0;
// 			ft_free_split(paths);
// 			return (res);
// 		}
// 		free(res);
// 		i++;
// 	}
// 	ft_free_split(paths);
// 	perror("child_where");
// 	fprintf(stderr, "returning NULL in child_where\n");
// 	return (NULL);
// }

// char	**where_get_paths(char **env)
// {
// 	int		i;
// 	char	**paths;

// 	i = 0;
// 	while (env[i] && ft_strncmp("PATH", env[i], 4))
// 		i++;
// 	if (!env[i])
// 		return (NULL);
// 	paths = ft_split(&env[i][5], ':');
// 	return (paths);
// }
char	*ft_strjoin_new(char *s1, char *s2)
{
	size_t	memsize;
	size_t	i;
	char	*new_str;
	size_t	len_s1;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	memsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	new_str = (char *)malloc(memsize * sizeof(char));
	if (new_str == NULL)
		return (NULL);
	i = -1;
	while (++i < memsize && s1[i] != '\0')
		new_str[i] = s1[i];
	while (i < memsize)
	{
		new_str[i] = s2[i - len_s1];
		i++;
	}
	free(s1);
	free(s2);
	return (new_str);
}

char	*child_where(char *cmd, char **paths)
{
	char	*cmd_path;
	int		i;

	i = 0;
	cmd_path = NULL;
	if (ft_strchr(cmd, '/') != 0)
		cmd_path = ft_strdup(cmd);
	else
	{
		while (paths[i] != NULL)
		{
			paths[i] = ft_strjoin_new(paths[i], ft_strdup("/"));
			paths[i] = ft_strjoin_new(paths[i], ft_strdup(cmd));
			if (access(paths[i], F_OK) == 0)
				cmd_path = ft_strdup(paths[i]);
			i++;
		}
	}
	free(cmd);
	free_split(paths);
	return (cmd_path);
}

char	**get_paths(char **env)
{
	int		i;
	char	*path;

	path = NULL;
	path = getenv("PATH");
	// i = 0;
	// while (env[i] != NULL)
	// {
	// 	if (ft_strncmp(env[i], "PATH=", 5) == 0)
	// 		path = &(env[i][5]);
	// 	i++;
	// }
	if (path == NULL)
		path = "./";
	return (ft_split(path, ':'));
}

char	*get_cmd(char *str)
{
	char	*ret;
	char	**tmp;

	tmp = ft_split(str, ' ');
	ret = ft_strdup(tmp[0]);
	free_split(tmp);
	return (ret);
}