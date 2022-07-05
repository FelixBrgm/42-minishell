/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limiter_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dhamdiev <dhamdiev@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 15:36:11 by fbruggem          #+#    #+#             */
/*   Updated: 2022/07/05 17:00:03 by dhamdiev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "children.h"

int	limiter_exec(t_child *child)
{
	char	*temp;
	char	*res;

	temp = readline("> ");
	res = NULL;
	while (temp && ft_strncmp(temp, child->limiter, ft_strlen(child->limiter) + 1) != 0)
	{
		temp = ft_strjoin_free(temp, "\n");
		res = ft_strjoin_free(res, temp);
		free(temp);
		temp = readline("> ");
	}
	printf("%s", res);
	free(temp);
	free(res);
	exit(0);
}