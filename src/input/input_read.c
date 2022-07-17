/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/16 20:50:26 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

//(line 19) check if just a new line
int	input_read(t_global *global)
{
	global->input = readline("minishell-6.9 ");
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
