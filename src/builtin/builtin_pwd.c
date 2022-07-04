/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:31:24 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/04 14:39:56 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_pwd()
{
	char	*res;

	res = NULL;
	res = getcwd(NULL, 0);
	printf("%s\n", res);
	free(res);
	return (0);
}