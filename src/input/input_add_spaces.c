/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_add_spaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:21:55 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/12 16:57:38 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//if portion of the str staring from index i has redirection returned value is > -1
//return 0 == single redir
//return 1 == double redir
//return -1 == error
//return -2 == no redirections
int	is_valid_redir(char *str, int i)
{
	if (str[i] == '<')
	{
		if (str[i + 1] != '<' && str[i + 1] != '>')
			return (0);
		if (str[i + 1] == '<' && str[i + 2] != '<' && str[i + 2] != '>')
			return (1);
		return (-1);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] != '<' && str[i + 1] != '>')
			return (0);
		if (str[i + 1] == '>' && str[i + 2] != '<' && str[i + 2] != '>')
			return (1);
		return (-1);
	}
	return (-2);
}

//Returns the len of a string after adding spaces before and after redirections
int	len_after_adding_spaces(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] != '\0')
	{
		if (is_valid_redir(str, i) > -1)
		{
			len += is_valid_redir(str, i) + 2;
			i += len - i - 2;
		}
		i++;
		len++;
	}
	return (len);
}

//Copy and skip the single quotes inside of str (single quotes are also copied)
void	copy_skip_squotes(char *ret_str, char *str, int *i, int *j)
{
		if (str[*i] == '\'' && ft_strchr(&(str[(*i) + 1]), '\'') != 0)
		{
			ret_str[*j] = str[*i];
			(*i)++;
			(*j)++;
			while (str[*i] != '\'' && str[*i] != '\0')
			{
				ret_str[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
			if (str[*i] == '\'')
			{
				ret_str[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
		}
}

//Copy and skip the double quotes inside of str (double quotes are also copied)
void	copy_skip_dquotes(char *ret_str, char *str, int *i, int *j)
{
		if (str[*i] == '\"' && ft_strchr(&(str[(*i) + 1]), '\"') != 0)
		{
			ret_str[*j] = str[*i];
			(*i)++;
			(*j)++;
			while (str[*i] != '\"' && str[*i] != '\0')
			{
				ret_str[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
			if (str[*i] == '\"')
			{
				ret_str[*j] = str[*i];
				(*i)++;
				(*j)++;
			}
		}
}

int	put_spaces(char *ret_str, char *str, int *i, int *j)
{
	int		tmp_i;

	tmp_i = -1;
	tmp_i = is_valid_redir(str, *i);
	if (tmp_i > -1)
	{
		ret_str[(*j)++] = ' ';
		while (tmp_i-- > -1)
		{
			ret_str[(*j)++] = str[(*i)++];
		}
		ret_str[(*j)++] = ' ';
	}
	else if (tmp_i == -1)
	{
		printf("Syntax error in redirs (add_spaces())\n");
		ft_protect(3, str, ret_str, NULL);
		return (-1);
	}
	return (0);
}

void	free_double(char *str1, char *str2)
{
	free(str1);
	free(str2);
}

char	*add_spaces(char *str)
{
	int		i;
	int		j;
	char	*ret_str;
	
	i = 0;
	j = 0;
	ret_str = malloc((len_after_adding_spaces(str) + 1) * sizeof(char));
	if (ret_str == NULL)
	{
		free(str);
		return (NULL);
	}
	while (str[i] != '\0')
	{
		copy_skip_squotes(ret_str, str, &i, &j);
		copy_skip_dquotes(ret_str, str, &i, &j);
		if (put_spaces(ret_str, str, &i, &j) == -1)
		{
			// free_double(str, ret_str);
			free(ret_str);
			return (NULL);
		}
		ret_str[j++] = str[i++];
	}
	ret_str[j] = '\0';
	free(str);
	return (ret_str);
}