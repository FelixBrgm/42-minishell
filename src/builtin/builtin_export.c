/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:53:48 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 20:35:19 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	builtin_export_print(char **env);
static int	export_update(char **env, char *text);

/**
 * @brief Mimiks the functionality from export 
 * 
 * @param cmd as { "export", "NAME=VALUE"}
 * @param env 
 * @return int 
 */
int	builtin_export(char	**cmd, char **env)
{
	int	i;

	if (!cmd[1])
		return (builtin_export_print(env));
	i = 1;
	while (cmd[i])
	{
		export_update(env, cmd[i]);
		i++;
	}
	// is it only export
		// then read them
	// otherwise add variable
	return (0);
}

static int	export_update(char **env, char *text)
{
	char *temp;
	char	**env_i;
	int	i;

	temp = ft_strdup(text);
	i = 0;
	while (temp[i] && temp[i] != '=')
		i++;
	temp[i] = '\0';
	env_i = export_get(env, temp);
	if (env_i)
		*env_i = ft_strdup(text);
	else
	{
		i = 0;
		while (env[i])
			i++;
		env[i] = ft_strdup(text);
		env[i + 1] = NULL;
	}
	free(temp);
	return (0);
}


char **export_get(char **env, char *name)
{
	int	i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, ft_strlen(name)) == 0 
			&& (env[i][ft_strlen(name)] == '=' || env[i][ft_strlen(name)] == '\0'))
				return (&env[i]);
		i++;
	}
	return (NULL);
}


static int	builtin_export_print(char **env)
{
	int	i;
	int	j;
	j = 0;
	while (env[j])
	{
		i = 0;
		printf("declare -x ");
		while (env[j][i] && env[j][i] != '=')
		{
			printf("%c", env[j][i]);
			i++;
		}
		if (env[j][i] == '=')
		{
			printf("%c", env[j][i]);
			i++;
			printf("%c", '"');
			while (env[j][i])
				printf("%c", env[j][i++]);
			printf("%c", '"');
		}
		printf("\n");
		j++;
	}
	return (0);
}