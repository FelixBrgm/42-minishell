/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:31:24 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/13 12:32:48 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief gives back the current absolute path
 * 
 * @return int 
 */
int	builtin_pwd(t_child *child)
{
	char	res[PATH_MAX];

	getcwd(res, PATH_MAX);
	printf("%s\n", res);
	if (close(STDIN_FILENO) < 0 && close(STDOUT_FILENO) < 0)
		return (1);
	return (0);
}
