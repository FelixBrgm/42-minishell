/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_sanitize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:42:29 by felixbrugge       #+#    #+#             */
/*   Updated: 2022/07/08 16:39:43 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static char *add_spaces(char *input);
static int	is_redir(char *str);
static void add_spaces_iter(char *str, int *i);
static void add_space(char *str);

int input_sanitize(char **input)
{
    *input = add_spaces(*input);   
    printf("%s\n", *input);
    return (0);
}

static char *add_spaces(char *input)
{
    char *temp;
    int i;
    
    i = 0;
    temp = NULL;
    temp = ft_calloc(ft_strlen(input) * 3 + 1, sizeof(char));
    ft_strlcpy(temp, input, ft_strlen(input));
    if (!temp)
        return (NULL);
    input_iter_brackets(temp, &add_spaces_iter, "\"\'", &i);
    return (temp);
}

static void add_spaces_iter(char *str, int *i)
{
    if (str[*i + 2])
    {
        if (is_redir(str) == 1)
        {
            add_space(str);
            *i += 2;
        }
        else if (is_redir(str) == 2)
        {
            add_space(&str[1]);
            *i += 3;
        }
        else 
            *i = *i + 1;
    }
}

/**
 * @brief Gets pointer and adds one space after the first character if its redirection | NEED enough room
 */
static void add_space(char *str)
{
    int i;

    if (!str)
        return ;
    i = ft_strlen(str);
    while (i > 1)
    {
        str[i] = str[i -1];
        i--;
    }
    str[1] = ' ';
}

/**
 * @brief 1 one redir | 2 double redir | -1 syntax error |
 */
static int	is_redir(char *str)
{
	if (str[0] == '<')
	{
		if (str[1] == '>')
			return (-1);
		if (str[1] == '<' && str[2] != '<' && str[2] != '>')
			return (2);
		if (str[1] != '<' && str[1] != '>')
			return (1);
	}
	if (str[0] == '>')
	{
		if (str[1] == '<')
			return (-1);
		if (str[1] == '>' && str[2] != '<' && str[2] != '>')
			return (2);
		if (str[1] != '<' && str[1] != '>')
			return (1);
	}
    return (0);
}