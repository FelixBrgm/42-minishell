/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:41:07 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/08 21:01:06 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	set_dredir_in(char	**tmp, t_global *global)
{
	int	j;
	int	lim;
	int	expand;

	j = 0;
	while (is_dredir_in_split(&tmp[j]) != -1 && tmp[j] != NULL)
	{
		lim = is_dredir_in_split(&tmp[j]) + 1;
		j += lim;
		if (tmp[j] == NULL)
		{
			printf("Syntax error near >>\n");
			return (1);
		}
		if (tmp[j][0] == '\"' || tmp[j][0] == '\'')
			expand = 0;
		else
			expand = 1;
		dlistadd_back(&global->children_head,
			dlistnew(NULL, NULL, NULL, rem_quotes(tmp[j]), expand));
	}
	return (0);
}

int	set_redir_in(char **tmp, t_global *global)
{
	t_child	*last_child;

	last_child = dlistlast(global->children_head);
	if (is_redir_in_split(tmp) != -1)
	{
		if (tmp[is_redir_in_split(tmp) + 1] == NULL)
		{
			printf("Syntax error near <\n");
			return (1);
		}
		last_child->file_in = ft_strdup(tmp[is_redir_in_split(tmp) + 1]);
	}
	return (0);
}

int	dredir_out_check(char **tmp, int i, t_global *global)
{
	t_child	*last_child;

	last_child = dlistlast(global->children_head);
	if (is_dredir_out(tmp[i]) != -1)
	{
		if (last_child->file_out_trunc != NULL)
		{
			free(last_child->file_out_trunc);
			last_child->file_out_trunc = NULL;
		}
		if (last_child->file_out_app != NULL)
			free(last_child->file_out_app);
		if (tmp[i + 1] == NULL)
			return (1);
		last_child->file_out_app = ft_strdup(tmp[i + 1]);
		listadd_back(&global->app_file_list_head, listnew(tmp[i + 1]));
	}
	return (0);
}

int	set_redirs_out(char **tmp, t_global *global)
{
	int		i;
	t_child	*last_child;

	i = -1;
	last_child = dlistlast(global->children_head);
	while (tmp[++i] != NULL)
	{
		if (is_redir_out(tmp[i]) != -1)
		{
			if (last_child->file_out_app != NULL)
			{
				free(last_child->file_out_app);
				last_child->file_out_app = NULL;
			}
			if (last_child->file_out_trunc != NULL)
				free(last_child->file_out_trunc);
			if (tmp[i + 1] == NULL)
				return (1);
			last_child->file_out_trunc = ft_strdup(tmp[i + 1]);
			listadd_back(&global->trunc_file_list_head, listnew(tmp[i + 1]));
		}
		if (dredir_out_check(tmp, i, global))
			return (1);
	}
	return (0);
}

int	set_files(char **split_input, t_global *global)
{
	char	**tmp;
	int		i;

	i = 0;
	while (split_input[i] != NULL)
	{
		tmp = split_mod(split_input[i], ' ');
		if (set_dredir_in(tmp, global) == 1)
		{
			free_split(tmp);
			return (1);
		}
		dlistadd_back(&global->children_head,
			dlistnew(NULL, NULL, NULL, NULL, 0));
		tmp = input_rem_quotes(tmp);
		if (set_redir_in(tmp, global) || set_redirs_out(tmp, global))
		{
			free_split(tmp);
			return (1);
		}
		free(tmp);
		i++;
	}
	return (0);
}
