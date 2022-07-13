/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:41:07 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/12 16:28:10 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	set_dredir_in(char	**tmp, t_global *global)
{
	int		j;
	int		lim;
	char	*file;
	int		expand;

	j = 0;
	while (is_dredir_in_split(&tmp[j]) != -1 && tmp[j] != NULL)
	{
		lim = is_dredir_in_split(&tmp[j]) + 1;
		j += lim;
		if (tmp[j] == NULL)
			return (1);
		if (tmp[j][0] == '\"' || tmp[j][0] == '\'')
			expand = 0;
		else
			expand = 1;
		file = set_vars(tmp[j], global->env);
		dlistadd_back(&global->children_head,
			dlistnew(NULL, NULL, NULL, rem_quotes(file), expand));
		free(file);
	}
	return (0);
}

int	set_redir_in(char **tmp, t_global *global)
{
	t_child	*last_child;
	char	*file;
	char	*tmp2;

	last_child = dlistlast(global->children_head);
	if (is_redir_in_split(tmp) != -1)
	{
		if (tmp[is_redir_in_split(tmp) + 1] == NULL)
			return (1);
		file = set_vars(tmp[is_redir_in_split(tmp) + 1], global->env);
		tmp2 = file;
		file = rem_quotes(file);
		last_child->file_in = ft_strdup(file);
		free(tmp2);
		free(file);
	}
	return (0);
}

int	dredir_out_check(char **tmp, int i, t_global *global)
{
	t_child	*last_child;
	char	*file;
	char	*tmp2;

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
		file = set_vars(tmp[i + 1], global->env);
		tmp2 = file;
		file = rem_quotes(file);
		last_child->file_out_app = ft_strdup(file);
		listadd_back(&global->app_file_list_head, listnew(file));
		free(tmp2);
	}
	return (0);
}

int	redir_out_check(char **tmp, int i, t_global *global)
{
	t_child	*last_child;
	char	*file;
	char	*tmp2;

	last_child = dlistlast(global->children_head);
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
		file = set_vars(tmp[i + 1], global->env);
		tmp2 = file;
		file = rem_quotes(file);
		last_child->file_out_trunc = ft_strdup(file);
		listadd_back(&global->trunc_file_list_head, listnew(file));
		free(tmp2);
	}
	return (0);
}

int	set_redirs_out(char **tmp, t_global *glob)
{
	int		i;
	t_child	*last_child;

	i = 0;
	last_child = dlistlast(glob->children_head);
	while (tmp[i] != NULL)
	{
		if (redir_out_check(tmp, i, glob) || dredir_out_check(tmp, i, glob))
			return (1);
		i++;
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
		if (set_redir_in(tmp, global) || set_redirs_out(tmp, global))
		{
			free_split(tmp);
			return (1);
		}
		free_split(tmp);
		i++;
	}
	return (0);
}
