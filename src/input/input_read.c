/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 20:58:25 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

void	input_read(t_global *global)
{
	global->input = readline("minishell-6.9 ");
	add_history(global->input);
	// printf("input: %s\n", global->input);
	input_parse(global);
}