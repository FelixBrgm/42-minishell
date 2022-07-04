/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:53:48 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 15:41:41 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_export(char	**cmd, char **env)
{
	// is it only export
		// then read them
	// otherwise add variable

	int	i;
	int	j;
	j = 0;
	while (env[j])
	{
		i = 0;
		while (env[j][i])
			printf("%c", env[j][i++]);
		printf("\n");
		j++;
	}
	return (0);
}