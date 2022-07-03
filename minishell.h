/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:15:45 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 18:55:09 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs/libs.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <termios.h>
# include "readline/history.h"
# include "readline/readline.h"

typedef struct s_child
{
	char	**cmd;
	char	**shell;
	int		fd_in;
	int		fd_out;
	char	*file_in;
	char	*file_out_trunc;
	char	*file_out_app;
	char	*limiter;
}				t_child;

typedef struct s_global
{
	// CONFIG
	char			*promt;
	int				interactive_mode;
	char			**env;
	struct termios	old_termios;
	//Runtime
	char			*input;
	t_child			**children;
}				t_global;

void	set_to_default(t_global	*global);

void	input_read(t_global *global);

void	children_exec(t_global *global);

void	global_free(t_global *global);

#endif