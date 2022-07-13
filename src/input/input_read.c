/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 16:51:49 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	input_read(t_global *global)
{
	global->input = readline("minishell-6.9 ");
	
	//check if just a new line
	if (ft_strlen(global->input) > 0)
		add_history(global->input);
	else
	{
		if (global->input == NULL)
		{
			printf("exit\n");
			exit(0);
		}
		return (1);
	}
	if (input_parse(global) == 1)
		return (1);
	return (0);
}