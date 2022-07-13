/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:25:31 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/12 21:31:39 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

# include "../../minishell.h"
# include "../utils/utils.h"

// Excecution
int	builtin_is_cmd(char **cmd, char **env);
int	builtin_exec(t_child *child, char **env);

// Shell Commands
int	builtin_echo(t_child *child);
int	builtin_cd(t_child *child, char **env);
int	builtin_pwd(t_child *child);
int	builtin_export(t_child *child, char **env);
int builtin_env(char **env, t_child *child);
int	builtin_unset(t_child *child, char **env);
int	builtin_exit(t_child *child);

#endif