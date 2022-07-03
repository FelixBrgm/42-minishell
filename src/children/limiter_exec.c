/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbruggem <fbruggem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:36:11 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/03 19:05:30 by fbruggem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int	limiter_exec(t_child *child)
{
	char	*temp;

	temp = readline("> ");
	while (temp && ft_strncmp(temp, child->limiter, ft_strlen(child->limiter) + 1) != 0)
	{
		printf("%s", temp);
		temp = readline("> ");
	}
	return (1);
}