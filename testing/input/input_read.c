/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:22:56 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/08 03:14:56 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int	input_read(t_global *global)
{
    global->input = NULL;
	global->input = readline("minishello> ");
    if (!global->input)
        return (1);
	add_history(global->input);
	input_parse(global);
    return (0);
}