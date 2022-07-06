/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_mod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 17:38:23 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/06 13:58:27 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "input.h"

char	*skip_char(char *str, char c)
{
	while (*str == c && *str != '\0')
		str++;
	return (str);
}

int	get_len_until_char(char *str, char c, char char_og)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		if (c == char_og && str[i] == '\'' && ft_strchr(&(str[i + 1]), '\'') != NULL)
			i += get_len_until_char(&str[i + 1], '\'', char_og);
		else if (c == char_og && str[i] == '\"' && ft_strchr(&(str[i + 1]), '\"') != NULL)
			i += get_len_until_char(&str[i + 1], '\"', char_og);
		else
			i++;
	}
	while (str[i] != '\0' && str[i] != char_og)
		i++;
	return (i);
}

int	get_len(char *str, char c)
{
	int	size;

	size = 0;
	if (*str == '\"' && ft_strchr(str + 1, '\"') != NULL)
		size = get_len_until_char(str + 1, '\"', c) + 1;
	else if (*str == '\'' && ft_strchr(str + 1, '\'') != NULL)
		size = get_len_until_char(str + 1, '\'', c) + 1;
	else
		size = get_len_until_char(str, c, c);
	return (size);
}

char	*copy_word(char *str, char c)
{
	int		i;
	int		j;
	char	*ret_str;
	int		size;

	i = 0;
	size = get_len(str, c);
	ret_str = malloc(size + 1);
	// if (*str == '\'' || *str == '\"')
	// 	str++;
	// printf("str = %s\n", str);
	while (i < size)
	{
		ret_str[i++] = *str;
		str++;
	}
	ret_str[i] = '\0';
	return (ret_str);
}

char	*skip_word(char *str, char c)
{
	int		i;
	int		size;

	i = 0;
	size = get_len(str, c);
	// printf("SIZE = %d\n", size);
	// printf("str = %s\n", str);
	// if (*str == '\'' || *str == '\"')
	// 	str++;
	while (i < size)
	{
		str++;
		i++;
	}
	return (str);
}

int	word_count(char *str, char c)
{
	int	count;

	count = 0;
	while (*(str) != '\0')
	{
		str = skip_char(str, c);
		if (*str != '\0')
			count++;
		str = skip_word(str, c);
	}
	return (count);
}

char	**split_mod(char *str, char c)
{
	char	**ret;
	int		i;
	int		size;

	if (str == NULL)
		return (NULL);
	size = word_count(str, c);
	ret = malloc((size + 1) * sizeof(char *));
	i = 0;
	while (i < size)
	{
		str = skip_char(str, c);
		if (*str != '\0')
		{
			ret[i] = copy_word(str, c);
			str = skip_word(str, c);
		}
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

//------------------DEBUG AND TESTING-----------------

// void	print_split(char **str)
// {
// 	int	i;

// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		if (i != 0)
// 			printf(" ");
// 		printf("<%s>", str[i]);
// 		i++;
// 	}
// 	printf("\n");
// }


// int main ()
// {
// 	char *test1 = "echo hello | cat -e";
// 	char *test2 = "echo \"hello   a\" | cat -e";
// 	char *test3 = "echo \"hello   a |\" cat -e";
// 	char *test4 = "echo \'hello   a |\' cat -e";
// 	char *test5 = "echo hello|cat -e";
// 	char **str = split_mod(test1, '|');
// 	print_split(str);
// 	str = split_mod(test2, '|');
// 	print_split(str);
// 	str = split_mod(test3, '|');
// 	print_split(str);
// 	str = split_mod(test4, '|');
// 	print_split(str);
// 	str = split_mod(test5, '|');
// 	print_split(str);
// }