/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 16:23:08 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/07 15:42:12 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_INPUT_H
# define MINISHELL_INPUT_H

# include "../../minishell.h"
# include "../utils/utils.h"

void	input_parse(t_global *global);
char	**split_mod(char *str, char c);
char	*rem_redirs(char *old_input);
void	set_null_children(t_global *global, int count);
void	clear_input(char **input, char **env);

//input_add_spaces
int		is_valid_redir(char *str, int i);
int		len_with_spaces(char *str);
char	*add_spaces(char *str);


//dredir_in
char	*get_dredir(char *str);
char	*rem_dredir_in(char *str);
char	**sep_dredir_in(int count, char **old_input);
int		is_dredir_in_split(char **str);
int		is_dredir_in(char *str);

//dredir_out
int		is_dredir_out(char *str);
char	*rem_dredir_out(char *str);

//redir_in
int		is_redir_in(char *str);
char	*rem_redir_in(char *str);

//redir_out
int		is_redir_out(char *str);
char	*rem_redir_out(char *str);

//set_vars
char	*set_vars(char *str, char **env);
int		get_expanded_len(char *str, char **env);
char	*get_var_name(char *str);


//utils
void	free_split(char **str);
void	print_split(char **str);
void	print_children(t_global *global);
int		split_len(char **str);
char	**split_dup(char **str);


#endif