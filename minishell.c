/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:50 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 17:09:34 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "src/builtin/builtin.h"

int	exit_code = 0;

void	setup_termios_new(t_global *global)
{
	struct termios term;

	tcgetattr(0, &global->old_termios);
	global->old_termios.c_cc[VEOF] = 4;
	global->old_termios.c_cc[VINTR] = 3;
	term = global->old_termios;
	term.c_cc[VEOF] = 3;
	term.c_cc[VINTR] = 4;
	tcsetattr(0, TCSANOW, &term);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

int	main(int argc, char **argv, char **env)
{
	t_global	global;
	struct sigaction	sa;

	sa.sa_handler = &handle_sigint;
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	set_to_default(&global, env);
	while (1)
	{
		// setup_termios_new(&global);
		if (input_read(&global) == 0)
		{
			// tcsetattr(0, TCSANOW, &global.old_termios);
			open_files(global.app_file_list_head, global.trunc_file_list_head);
			children_exec(&global);;
		}
	}
	// set_to_default(global);
	// while (1)
	// {
	// 	input_read(global);
	// 	child_exec(global);
	// 	children_free(global);
	// }
	return (0);
}