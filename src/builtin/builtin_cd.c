/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 19:20:53 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 20:43:28 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"


/**
 * @brief Cd's into the given directory
 * 
 * @param cmd as { "cd", "DIR" }
 * @return int 
 */
int	builtin_cd(char **cmd, char **env)
{
	char **pwd;
	char **pwd_old;
	if (!cmd)
		return (1);
	pwd = export_get(env, "PWD");
	pwd_old = export_get(env, "OLDPWD");
	*pwd_old = ft_strjoin("OLD", *pwd);
	if (chdir(cmd[1]))
		return (1); // ALSO THROW AN ERROR
	*pwd = ft_strjoin("PWD=", getcwd(NULL, 0));
	return (0);
}