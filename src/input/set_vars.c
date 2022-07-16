/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 15:38:49 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/16 22:14:25 by fbruggem         ###   ########.fr       */
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

void	len_helper(char *str, int *i, int *size, char **env)
{
	int		squote;
	int		dquote;
	char	*var_name;

	squote = 0;
	dquote = 0;
	var_name = NULL;
	if (str[*i] == '\"' && ft_strchr(&str[(*i) + 1], '\"') != 0 && squote == 0)
		dquote = 1;
	if (str[*i] == '\'' && ft_strchr(&str[(*i) + 1], '\'') != 0 && dquote == 0)
		squote = 1;
	if (str[*i] == '$' && squote == 0)
	{
		var_name = get_var_name(&(str[(*i) + 1]));
		*size += ft_strlen(env_get_value(env, var_name));
		*i += ft_strlen(var_name);
		free(var_name);
	}
	else
		(*size)++;
	(*i)++;
	if (str[*i] == '\'' && squote == 1)
		squote = 0;
	if (str[*i] == '\"' && dquote == 1)
		dquote = 0;
}

int	get_expanded_len(char *str, char **env)
{
	int		size;
	int		i;

	i = 0;
	size = 0;
	while (str != NULL && str[i] != '\0')
		len_helper(str, &i, &size, env);
	return (size);
}

char	*set_vars(char *str, char **env)
{
	char	*ret_str;
	int		i;
	int		j;
	char 	*value;
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
			value = ft_strdup(env_get_value(env, var_name));
			ft_strlcpy(&(ret_str[j]), value, ft_strlen(value) + 1);
			j += ft_strlen(value);
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
	return (ret_str);
}

///usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki