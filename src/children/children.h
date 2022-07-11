/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:25:31 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/11 15:45:53 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CHIDLREN_H
# define MINISHELL_CHIDLREN_H

# include "../../minishell.h"
# include "../builtin/builtin.h"

void	child_exec(t_child *child, char **env, int free_pipe);
int		limiter_exec(t_child *child, char **env);
void	children_free(t_global *global);
char	*child_where( char *cmd,char **paths);
char	**get_paths(char **env);
char	*get_cmd(char *str);

#endif