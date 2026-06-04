/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_rotate_a_b.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 02:48:54 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/25 03:10:41 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static int rev_rotate(t_swap **stack)
{
	t_swap *last;
	t_swap *first;

	if (!stack || !*stack || (*stack)->next == NULL)
		return (0);
	first = *stack;
	last = *stack;
	while (last->next)
		last = last->next;
	last->pre->next = NULL;
	last->next = first;
	first->pre = last;
	last->pre = NULL;
	*stack = last;
	return (1);
}

void    rev_rotate_a(t_swap **stack_a)
{
    if (rev_rotate(stack_a) == 1)
        write(1, "rra\n", 4);
}

void    rev_rotate_b(t_swap **stack_b)
{
    if (rev_rotate(stack_b) == 1)
        write(1, "rrb\n", 4);
}

void    rev_rotate_r(t_swap **stack_a, t_swap **stack_b)
{
    int check_a;
    int check_b;

    check_a = rev_rotate(stack_a);
    check_b = rev_rotate(stack_b);
    if (check_a == 1 || check_b == 1)
        write(1, "rrr\n", 4);
}
/*
#include <stdio.h>

// テスト用：スタックの状態を上から順番にプリントする関数
void    print_stack_debug(t_swap *stack)
{
    if (!stack)
    {
        printf("(empty)\n");
        return ;
    }
    while (stack)
    {
        printf("[%d] ", stack->num);
        // 双方向の繋がり（pre）が壊れていないかチェック
        if (stack->pre)
            printf("(pre:%d) ", stack->pre->num);
        else
            printf("(pre:NULL) ");

        stack = stack->next;
    }
    printf("\n");
}

int main(void)
{
    // 1. スタックA用のノードを3つ作成 [1, 2, 3]
    t_swap a1, a2, a3;

    a1.num = 1;
    a1.pre = NULL;
    a1.next = &a2;

    a2.num = 2;
    a2.pre = &a1;
    a2.next = &a3;

    a3.num = 3;
    a3.pre = &a2;
    a3.next = NULL;

    // 2. 先頭を指すポインタ変数を用意
    t_swap *stack_a = &a1;

    // 実行前の状態を表示
    printf("【Before Reverse Rotate】\n");
    printf("Stack A: ");
    print_stack_debug(stack_a);
    printf("----------------------------------------\n\n");

    // 3. rra を実行（末尾の [3] を一番前へシフト！）
    rev_rotate_a(&stack_a);

    // 実行後の状態を表示
    printf("\n【After rra】\n");
    printf("Stack A: ");
    print_stack_debug(stack_a);
    printf("----------------------------------------\n");

    return (0);
}
*/
