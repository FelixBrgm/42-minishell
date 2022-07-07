/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:33:35 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/07 11:52:44 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../minishell.h"

// utils_env.c

char **env_get(char **env, char *name);
char **env_update(char **env, char *name, char *value, int equal_sign);
char *env_get_value(char **env, char *name);
char **env_extend(char **env);

#endif