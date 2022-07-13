/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_rem_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:33:05 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/08 21:02:33 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

char	*remove_first_character(char *str)
{
	int	i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
	{
		str[i] = str[i + 1];
		i++;
	}	
	str[i -1] = '\0';
	return (str);
}

char	*rem_quotes(char *str)
{
	int	status; // 0 Nothing encountered | 1 "" | 2 ''
	int 	i;
	char *res;
	
	i = 0;
	status = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (status == 0)
		{
			if (str[i] == '\"')
			{
				status = 1;
				remove_first_character(&str[i]);
			}
			else if (str[i] == '\'')
			{
				status = 2;
				remove_first_character(&str[i]);
			}
			else 
				i++;
		}
		else if (status == 1 && str[i] == '\"')
		{
			status = 0;
				remove_first_character(&str[i]);
		}
		else if (status == 2 && str[i] == '\'')
		{
			status = 0;
				remove_first_character(&str[i]);
		}
		else
			i++;
	}
	res = ft_strdup(str);
	return (res);
}

char	**input_rem_quotes(char **input)
{
	int		i;
	char	**tmp;

	i = 0;
	if (input == NULL)
		return NULL;
	tmp = malloc((split_len(input) + 1) * sizeof(char *));
	while (input[i] != NULL)
	{
		tmp[i] = rem_quotes(input[i]);
		i++;
	}
	tmp[i] = NULL;
	free_split(input);
	return(tmp);
}
//echo < 1 >>outfile_app1 >>otufile_app_2 < infile_2 <<here_doc1 <infile3 >otufile1_trunc