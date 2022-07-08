/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:28:34 by felixbrugge       #+#    #+#             */
/*   Updated: 2022/07/08 03:16:07 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int input_parse(t_global *global)
{
    //printf("INPUT: %s\n", global->input);
    input_sanitize(&global->input);
    // Input sanitize
    // env_extension
    // split mod
    // Go over each splited and create children and add to the right
        // in out file < >> >
        // limiter <<
        // get actual command
        
}