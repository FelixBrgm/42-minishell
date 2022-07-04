/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:50 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 23:58:18 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "src/builtin/builtin.h"



int	main(int argc, char **argv, char **env)
{
	t_global	global;

	set_to_default(&global, env);
	builtin_export(NULL, global.env);
	while (1)
	{
		input_read(&global);
		children_exec(&global);
	}
	// set_to_default(global);
	// while (1)
	// {
	// 	input_read(global);
	// 	child_exec(global);
	// 	children_free(global);
	// }
	return (0);
}