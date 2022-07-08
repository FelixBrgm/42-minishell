/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felixbruggemann <felixbruggemann@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 02:54:27 by felixbrugge       #+#    #+#             */
/*   Updated: 2022/07/08 03:43:37 by felixbrugge      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

static int is_bracket(char c, char *brackets);
/**
 * @brief Interates over a string str and executes f() when not inside one of the brackets declared in brackets
 *        current_bracket = -1 not in bracket | n in the corresponding bracket
 */
int input_iter_brackets(char *str, void (*f)(char *, int *i), char *brackets, int *i)
{
    int j;
    int current_bracket;

    if (!str || !f || !brackets)
        return (1);
    j = 0;
    current_bracket = -1;
    while (str[j])
    {
        if (current_bracket == -1 && is_bracket(str[j], brackets) == -1)
            f(&str[j], i);
        else if (current_bracket == -1 && is_bracket(str[j], brackets) != -1)
            current_bracket = is_bracket(str[j], brackets);
        else if (current_bracket != -1 && current_bracket == is_bracket(str[j], brackets))
            current_bracket = -1;
        j++;
    }
    return (0);
}

static int is_bracket(char c, char *brackets)
{
    int i;

    i = 0;
    while (brackets[i])
    {
        if (brackets[i] == c)
            return (i);
        i++;
    }
    return (-1);
}