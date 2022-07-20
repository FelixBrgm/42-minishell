/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/20 15:49:38 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//(line 19) check if just a new line
int	input_read(t_global *global)
{
	if (isatty(0))
		global->input = readline("minishell-6.9 ");
	else
		global->input = get_next_line(0);
	if (ft_strlen(global->input) > 0)
		add_history(global->input);
	else
	{
		if (global->input == NULL)
		{
			if (isatty(0))
				printf("exit\n");
			exit(0);
		}
		return (1);
	}
	if (input_parse(global) == 1)
		return (1);
	return (0);
}
