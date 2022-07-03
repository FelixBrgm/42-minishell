/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:25:31 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 19:04:14 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

#include "../../minishell.h"

// Excecution
int	builtin_is_cmd(char **cmd, char **env);
int	builtin_exec(char **cmd, char **env);

// Shell Commands
int	builtin_echo(char **cmd, char ** env);
int	builtin_echo_n(char **cmd, char ** env);

#endif