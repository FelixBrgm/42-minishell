/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 14:31:24 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 13:04:08 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

/**
 * @brief gives back the current absolute path
 * 
 * @return int 
 */
int	builtin_pwd(void)
{
	char	*res;
	res = NULL;
	res = getcwd(NULL, 0);
	printf("%s\n", res);
	free(res);
	return (0);
}