/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:49 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/07 19:32:10 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;

	i = 0;
	while (str[i] != '\0' && str[i] != '\'' && str[i] != '\"')
	{
		if (str[i] == ' ' || str[i] == '|' || str[i] == '<' || str[i] == '>')
			break ;
		i++;
	}
	var_name = ft_strdup_i(str, i);
	if (var_name == NULL || var_name[0] == '\0')
	{
		free(var_name);
		return (NULL);
	}
	return (var_name);
}

int	get_expanded_len(char *str, char **env)
{
	int		size;
	int		i;
	char	*var_name;
	int		squote;
	int		dquote;

	i = 0;
	size = 0;
	squote = 0;
	dquote = 0;
	var_name = NULL;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"') != 0 && squote == 0)
			dquote = 1;
		if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'') != 0 && dquote == 0)
			squote = 1;
		if (str[i] == '$' && squote == 0)
		{
			var_name = get_var_name(&(str[i + 1]));
			size += ft_strlen(env_get_value(env, var_name));
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
			size++;
		i++;
		if (str[i] == '\'' && squote == 1)
			squote = 0;
		if (str[i] == '\"' && dquote == 1)
			dquote = 0;
	}
	return (size);
}

//to trash, the get_expanded_len should work test that !!!
char	*set_vars(char *str, char **env)
{
	char	*ret_str;
	int		i;
	int		j;
	char	*var_name;
	int		squote;
	int		dquote;

	i = 0;
	j = 0;
	squote = 0;
	dquote = 0;
	var_name = NULL;
	ret_str = malloc(get_expanded_len(str, env) + 1);
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] == '\"' && ft_strchr(&str[i + 1], '\"') != 0 && squote == 0)
			dquote = 1;
		if (str[i] == '\'' && ft_strchr(&str[i + 1], '\'') != 0 && dquote == 0)
			squote = 1;
		if (str[i] == '$' && squote == 0)
		{
			var_name = get_var_name(&(str[i + 1]));
			ft_strlcpy(&(ret_str[j]), env_get_value(env, var_name), ft_strlen(env_get_value(env, var_name)) + 1);
			j += ft_strlen(env_get_value(env, var_name));
			i += ft_strlen(var_name);
			free(var_name);
		}
		else
			ret_str[j++] = str[i];
		i++;
		if (str[i] == '\'' && squote == 1)
			squote = 0;
		if (str[i] == '\"' && dquote == 1)
			dquote = 0;
	}
	ret_str[j] = '\0';
	free(str);
	return (ret_str);
}

///usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki