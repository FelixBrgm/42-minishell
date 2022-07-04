/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:50 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 16:51:50 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "src/builtin/builtin.h"



int	main(int argc, char **argv, char **env)
{
	t_global	global;

	set_to_default(&global, env);
	builtin_export(NULL, global.env);
	// while (1)
	// 	input_read(&global);
	// set_to_default(global);
	// while (1)
	// {
	// 	input_read(global);
	// 	child_exec(global);
	// 	children_free(global);
	// }
	return (0);
}