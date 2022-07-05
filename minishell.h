/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:15:45 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 14:57:34 by dhamdiev         ###   ########.fr       */
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
# include <sys/errno.h>

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
 
int		set_to_default(t_global	*global, char **env);

void	input_read(t_global *global);

void	children_exec(t_global *global);

void	global_free(t_global *global);
// Built In
int		builtin_exec(char **cmd, char **env);
#endif