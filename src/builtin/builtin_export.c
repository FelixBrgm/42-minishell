/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:53:48 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/06 15:41:37 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

static int	builtin_export_print(char **env);
static int	export_update(char **env, char *text);
char *convert_to_name(char *text);
char *convert_to_value(char *text);
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

static int export_update(char **env, char *text)
{
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	name = convert_to_name(text);
	value = convert_to_value(text);
	if (ft_protect(2, name, value))
		return (1);
	if (!env_update(env, name, value))
		return (1);
	free(name);
	free(value);
	return (0);
}


/**
 * @brief gets name of text | ALLOCATES
 * 
 * @param text 
 * @return char* 
 */
char *convert_to_name(char *text)
{
	int	i;
	char *temp;
	char *res;
	if (!text)
		return (NULL);
	i = 0;
	temp = NULL;
	temp = ft_strdup(text);
	if (!temp)
		return (NULL);
	while (temp[i] && temp[i] != '=')
		i++;
	res = (ft_strdup_i(temp, i));
	free(temp);
	return (res);
}

/**
 * @brief | ALLOCATES
 * 
 * @param text 
 * @return char* 
 */
char *convert_to_value(char *text)
{
	int	i;
	char *temp;
	char *res;
	
	if (!text)
		return (NULL);
	i = 0;
	temp = NULL;
	temp = ft_strdup(text);
	if (!temp)
		return (NULL);
	while (temp[i] && temp[i] != '=')
		i++;
	res = (ft_strdup_i(&temp[i + 1], ft_strlen(temp) - i));
		free(temp);
	return (res);
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