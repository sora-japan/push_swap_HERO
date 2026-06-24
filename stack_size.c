/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/24 21:51:09 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/24 22:28:46 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int stack_size(t_swap *stack)
{
    int count;

    count = 0;
    while (stack != NULL)
    {
        count++;
        stack = stack->next;
    }
    return (count);
}
