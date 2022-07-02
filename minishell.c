/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:50 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/02 17:41:41 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_global	global;

	
	while (1)
		input_read(&global);
	// set_to_default(global);
	// while (1)
	// {
	// 	input_read(global);
	// 	children_exec(global);
	// 	children_free(global);
	// }
	return (0);
}