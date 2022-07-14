/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse_test.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:21:55 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/14 13:29:23 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		count_and_init_children(t_global *global, char **split_input);
int		get_count_children(t_global *global, char **split_input);
void	print_files(t_file_node *list);

int	input_parse(t_global *global)
{
	char	**split_input;
	char	*input_copy;

	global->children_head = NULL;
	global->trunc_file_list_head = NULL;
	global->app_file_list_head = NULL;
	input_copy = add_spaces(global->input);
	global->input = ft_strdup(input_copy);
	split_input = split_mod(global->input, '|');
	// split_input = input_expand(split_input, global->env);

	if (split_input == NULL || set_files(split_input, global) || split_input[0] == NULL)
	{
		printf("Syntax error \n");
		return 1;
	} // syntax error
	//printf("HEY\n");
	split_input = input_clear_redirs(split_input);
	clear_and_set_cmds(split_input, global);
	// debug
	print_children(global->children_head);
	printf("App files\n");
	print_files(global->app_file_list_head);
	printf("Trunc files\n");
	print_files(global->trunc_file_list_head);
	return (0);
}

int	split_len(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}

char	**split_dup(char **str)
{
	char	**ret;
	int		count;
	int		i;

	count = split_len(str);
	ret = malloc((count + 1) * sizeof(char *));
	i = 0;
	while (str[i] != NULL)
	{
		ret[i] = ft_strdup(str[i]);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

void	print_split(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		printf("%s\n", str);
		return ;
	}
	while (str[i] != NULL)
	{
		if (i != 0)
			printf(" ");
		printf("~%s~", str[i]);
		i++;
	}
	printf("\n");
}

void free_split(char **str)
{
	int	i;

	i = 0;
	while (str != NULL && str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	if (str != NULL)
		free(str);
}

void	print_children(t_child *list)
{
	int i = 0;
	while (list != NULL)
	{
		printf("CHILD index %d \n", i);
		printf("cmd:\t");
		print_split(list->cmd);
		printf("fd_in:\t%d\n", list->fd_in);
		printf("fd_out:\t%d\n", list->fd_out);
		printf("file_in:\t%s\n", list->file_in);
		printf("file_out_trunc:\t%s\n", list->file_out_trunc);
		printf("file_out_app:\t%s\n", list->file_out_app);
		printf("limiter.lim:\t%s\n", list->limiter.lim);
		printf("limiter.expand:\t%d\n", list->limiter.expand);
		printf("-----------------------------------------\n");
		list = list->next;
		i++;
	}
}

void	print_files(t_file_node *list)
{
	printf("\n-----------------------------\n");
	while (list != NULL)
	{
		printf("FIlE = %s\n", list->path);
		list = list->next;
	}
	printf("\n-----------------------------\n");
}
