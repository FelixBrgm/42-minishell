/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 11:33:35 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/16 20:26:28 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../../minishell.h"

// utils_env
char		**env_get(char **env, char *name);
char		**env_update(char **env, char *name, char *value, int equal_sign);
char		*env_get_value(char **env, char *name);
char		**env_extend(char **env);

//utils_dllist
t_child		*dlistnew(char *f_in, char *f_out_t, char *f_out_a,
				t_limiter limiter);
t_child		*dlistlast(t_child *lst);
void		dlist_rem(t_child **lst, char *str);
void		dlistadd_front(t_child **lst, t_child *new_lst);
void		dlistadd_back(t_child **lst, t_child *new_lst);

//utils_llist
t_file_node	*listnew(char *file);
t_file_node	*listlast(t_file_node *lst);
void		list_rem(t_file_node **lst, char *str);
void		listadd_back(t_file_node **lst, t_file_node *new_lst);
void		listadd_front(t_file_node **lst, t_file_node *new_lst);

// Free
int			children_free(t_child *head);
int			global_free(t_global *global);

//utils_redirs
int			is_valid_redir(char *str, int i);
int			set_redirs_out(char **tmp, t_global *glob);
int			set_dredir_in(char	**tmp, t_global *global);
int			set_redir_in(char **tmp, t_global *global);

#endif