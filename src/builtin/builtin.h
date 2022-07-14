/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:25:31 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/15 00:09:52 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILDIN_H

# include "../../minishell.h"
# include "../utils/utils.h"

// Excecution
int	builtin_is_cmd(char **cmd, char **env);
int	builtin_exec(t_child *child, char **env);

// Shell Commands
int	builtin_echo(t_child *child);
int	builtin_cd(t_child *child, char **env);
int	builtin_pwd(void);
int	builtin_export(t_child *child, char **env);
int	builtin_env(char **env, t_child *child);
int	builtin_unset(t_child *child, char **env);
int	builtin_exit(t_child *child);

#endif