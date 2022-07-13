/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 14:50:34 by fbruggem         ###   ########.fr       */
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
		return (1);
	if (input_parse(global) == 1)
		return (1);
	return (0);
}