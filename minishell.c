/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 14:14:50 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/16 20:35:03 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "src/builtin/builtin.h"

int	g_exit_code = 0;

void	setup_termios_new(t_global *global)
{
	struct termios term;

	tcgetattr(0, &global->old_termios);
	// global->old_termios.c_cc[VEOF] = 4;
	// global->old_termios.c_cc[VINTR] = 3;
	term = global->old_termios;
	// term.c_cc[VEOF] = 3;
	// term.c_cc[VINTR] = 4;
	term.c_lflag = ECHO | ISIG;
	tcsetattr(0, TCSANOW, &term);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		// write(1, "\n", 1);
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

	if (!argv || argc != 1)
		return (1);
	setup_termios_new(&global);
	sa.sa_handler = &handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	set_to_default(&global, env);
	while (1)
	{
		if (input_read(&global) == 0)
		{
			open_files(global.app_file_list_head, global.trunc_file_list_head);
			children_exec(&global);
			children_free(global.children_head);
			sigaction(SIGINT, &sa, NULL);
			free(global.input);
		}
	}
	global_free(&global);

	printf("HELLO\n");
	return (0);
}