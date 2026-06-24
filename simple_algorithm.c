/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_algorithm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 15:09:08 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/24 21:51:27 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// STAGE 3：ヘルパー関数②「最小値のインデックスを求める」 スタックの先頭を index=0 として、最>小値が何番目にあるかを返します。
static int find_min_index(t_swap *stack)
{
    int i;
    int min;
    int count;

    if (stack == NULL)
        return (-1);
    i = 0;
    count = 0;
    min = stack->num;
    while (stack != NULL)
    {
        if (min > stack->num)
        {
            min = stack->num;
            i = count;
        }
        stack = stack->next;
        count++;
    }
    return (i);
}

// STAGE 4：最小値を先頭に持ってくる インデックスとサイズをもとに、どちら向きに回転するか決め>ます。
// 最小値を先頭に持ってくる
static void bring_min_to_top(t_swap **a, int min_index, int size)
{
    int i;

    i = 0;
    if (min_index <= size / 2)
    {
        while (i < min_index)
        {
            rotate_ra(a);
            i++;
        }
    }
    else
    {
        while (i < (size - min_index))
        {
            rev_rotate_a(a);
            i++;
        }
    }
}

// main での呼び出しイメージ：
// t_swap *a = stack_init(*av);
// t_swap *b = NULL;        ← b は最初空
// simple_algorithm(&a, &b);

void simple_algorithm(t_swap **a, t_swap **b)
{
    int n;
    int i;
    int min_index;
    int size;

    n = stack_size(*a);
    if (n <= 1)
        return ;
    i = 0;
    while (i < n - 2)
    {
        min_index = find_min_index(*a);
        size = stack_size(*a);
        bring_min_to_top(a, min_index, size);
        push_pb(a, b);
        i++;
    }
    if ((*a)->num > (*a)->next->num)
        swap_sa(*a);
    while (*b != NULL)
        push_pa(a, b);
}
