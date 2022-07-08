/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:23:08 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/08 03:43:44 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INPUT_H
# define MINISHELL_INPUT_H

# include "../../minishell.h"
# include "../utils/utils.h"

// Input parse
int input_parse(t_global *global);

// Input sanitize
int input_sanitize(char **input);

// Utils
int input_iter_brackets(char *str, void (*f)(char *, int *i), char *brackets, int *i);

#endif