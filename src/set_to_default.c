/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_to_default.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:24:47 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 15:29:27 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	set_to_default(t_global	*global, char **env)
{
	int	i;
	
	i = 0;
	global->env = ft_calloc(1024, sizeof(char *));
	if (global->env)
		while (i < 1024)
			global->env[i++] = NULL;
	i = 0;
	while (env[i])
	{
		global->env[i] = ft_strdup(env[i]);
		i++;
	}
	return (0);
}