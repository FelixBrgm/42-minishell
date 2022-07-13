/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:21:55 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/11 15:35:57 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int		count_and_init_children(t_global *global, char **split_input);
int		get_count_children(t_global *global, char **split_input);
int		set_files(t_global *global, char *str, int child_i);

void	input_parse(t_global *global)
{
	int		children_count;
	char	**split_input;
	char	**split_input_copy;
	int		i;

	i = 0;
	global->input = add_spaces(global->input);
	split_input = split_mod(global->input, '|');
	split_input_copy = split_dup(split_input);
	children_count = count_and_init_children(global, split_input);
	printf("child count = %d\n", children_count);
	set_null_children(global, children_count);
	split_input = sep_dredir_in(children_count, split_input);
	if (split_input == NULL)
	{
		printf("SYNTAX ERROR\n");
		return ;
	}
	while (i < children_count && split_input[i] != NULL)
	{
		if (set_files(global, split_input[i], i) == 1)
		{
			printf("SYNTAX ERROR\n");
			return ;
		}
		i++;
	}
	clear_input(split_input_copy, global->env);
	if (split_input_copy[0] == NULL)
	{
		printf("SYNTAX ERROR\n");
		free(split_input_copy);
		//need to free children here
		global->children[0] = NULL;
		return ;
	}
	int x = 0;
	int	j = 0;
	while (global->children[x] != NULL)
	{
		//printf("child %d limiter == %s\n", x, global->children[x]->limiter);
		if (global->children[x]->limiter == NULL)
		{
			global->children[x]->cmd = split_mod(split_input_copy[j], ' ');
			//printf("j = %d\n", j);
			j++;
		}
		x++;
	}
	print_children(global);

}

char *remove_first_character(char *str)
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
	free(str);
	return (res);
}

void	clear_input(char **input, char **env)
{
	int	i;

	i = 0;
	if (input == NULL)
		return ;
	while (input[i] != NULL)
	{
		input[i] = rem_redirs(input[i]);
		input[i] = set_vars(input[i], env);
		input[i] = rem_quotes(input[i]);
		i++;
	}
}

char	*rem_redirs(char *old_input)
{
	char	*ret;

	ret = NULL;
	ret = rem_dredir_out(old_input);
	ret = rem_dredir_in(ret);
	ret = rem_redir_in(ret);
	ret = rem_redir_out(ret);
	return (ret);
}

void	set_null_children(t_global *global, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		global->children[i]->cmd = NULL;
		global->children[i]->shell = NULL;
		global->children[i]->fd_in = 0;
		global->children[i]->fd_out = 0;
		global->children[i]->file_in = NULL;
		global->children[i]->file_out_app = NULL;
		global->children[i]->file_out_trunc = NULL;
		global->children[i]->limiter = NULL;
		i++;
	}
}

//function leaks, free(tmp) before return(1)
int	set_files(t_global *global, char *str, int child_i)
{
	char	**tmp;

	tmp = split_mod(str, ' ');
	if (is_dredir_in(str) > -1)
		global->children[child_i]->limiter = ft_strdup(tmp[0]);
	if (is_dredir_out(str) > -1)
	{
		if (tmp[is_dredir_out(str) + 1] == NULL)
			return (1);
		global->children[child_i]->file_out_app = ft_strdup(tmp[is_dredir_out(str) + 1]);
	}
	if (is_redir_out(str) > -1)
	{
		if (tmp[is_redir_out(str) + 1] == NULL)
			return (1);
		global->children[child_i]->file_out_trunc = ft_strdup(tmp[is_redir_out(str) + 1]);
	}
	if (is_redir_in(str) > -1)
	{
		if (tmp[is_redir_in(str) + 1] == NULL)
			return (1);
		global->children[child_i]->file_in = ft_strdup(tmp[is_redir_in(str) + 1]);
	}
	free_split(tmp);
	return (0);
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
	char	**tmp;
	int		count;
	int		i;

	count = split_len(split_input);
	i = 0;
	while (split_input[i] != NULL)
	{
		tmp = split_mod(split_input[i], ' ');
		if (is_dredir_in_split(tmp) > -1)
			count++;
		free_split(tmp);
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
		printf("-----------------------------------------\n");
		i++;
	}
}
