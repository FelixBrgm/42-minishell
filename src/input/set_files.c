/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_files.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 18:41:07 by dhamdiev          #+#    #+#             */
/*   Updated: 2022/07/16 21:58:03 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	dredir_out_check(char **tmp, int i, t_global *global)
{
	t_child	*last_child;
	char	*file;

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
		file = rem_quotes(tmp[i + 1]);
		last_child->file_out_app = ft_strdup(file);
		listadd_back(&global->app_file_list_head, listnew(file));
	}
	return (0);
}

int	redir_out_check(char **tmp, int i, t_global *global)
{
	t_child	*last_child;
	char	*file;

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
		file = rem_quotes(tmp[i + 1]);
		last_child->file_out_trunc = ft_strdup(file);
		listadd_back(&global->trunc_file_list_head, listnew(file));
	}
	return (0);
}

int	set_files(char **split_input, t_global *global)
{
	char		**tmp;
	int			i;
	t_limiter	lim;

	i = 0;
	while (split_input[i] != NULL)
	{
		tmp = split_mod(split_input[i], ' ');
		if (set_dredir_in(tmp, global) == 1)
		{
			ft_free_split(tmp);
			return (1);
		}
		lim.lim = NULL;
		lim.expand = 0;
		dlistadd_back(&global->children_head, dlistnew(NULL, NULL, NULL, lim));
		if (set_redir_in(tmp, global) || set_redirs_out(tmp, global))
		{
			ft_free_split(tmp);
			return (1);
		}
		ft_free_split(tmp);
		i++;
	}
	return (0);
}
