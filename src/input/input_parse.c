/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:21:55 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 19:18:23 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		split_len(char **str);
int		count_and_init_children(t_global *global, char **split_input);
int		get_count_children(t_global *global, char **split_input);
void	print_children(t_global *global);
void	print_split(char **str);

void	input_parse(t_global *global)
{
	int		children_count;
	char	**split_input;

	split_input = ft_split(global->input, '|');
	children_count = count_and_init_children(global, split_input);
	while ()
}

int	count_and_init_children(t_global *global, char **split_input)
{
	int	count;
	int	i;

	i = 0;
	count = get_count_children(global, split_input);
	global->children = malloc((count + 1) * sizeof(t_child *));
	while (i < count)
	{
		global->children[i] = malloc(sizeof(t_child));
		i++;
	}
	global->children[i] = NULL;
	return (count);
}

int	get_count_children(t_global *global, char **split_input)
{
	int		count;
	int		i;
	int		j;

	count = split_len(split_input);
	i = 0;
	while (split_input[i] != NULL)
	{
		j = 0;
		while (split_input[i][j] != '\0')
		{
			if (split_input[i][j] == '<' && split_input[i][j + 1] == '<')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

int	split_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

void	print_split(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (i != 0)
			printf(" ");
		printf("|%s|", str[i]);
		i++;
	}
	printf("\n");
}

void	print_children(t_global *global)
{
	int	i;

	i = 0;
	while (global->children[i] != NULL)
	{
		printf("CHILD index %d \n", i);
		printf("cmd:\t");
		print_split(global->children[i]->cmd);
		printf("fd_in:\t%d\n", global->children[i]->fd_in);
		printf("fd_out:\t%d\n", global->children[i]->fd_out);
		printf("file_in:\t%s\n", global->children[i]->file_in);
		printf("file_out_trunc:\t%s\n", global->children[i]->file_out_trunc);
		printf("file_out_app:\t%s\n", global->children[i]->file_out_app);
		printf("limiter:\t%s\n", global->children[i]->limiter);
		printf("-----------------------------------------\n")
		i++;
	}
}

int	find_dredirection(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' && str[i + 1] == '<')
			return (1);
		i++;
	}
}