/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   children.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:25:31 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 17:07:51 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_CHIDLREN_H
# define MINISHELL_CHIDLREN_H

# include "../../minishell.h"
# include "../builtin/builtin.h"

int		child_exec(t_child *child, char **env);
void	limiter_exec(t_child *child);
void	children_free(t_global *global);

#endif