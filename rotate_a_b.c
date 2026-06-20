/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_a_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 01:53:00 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/20 14:48:52 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static int	rotate_a_b(t_swap **stack)
{
	t_swap	*first;
	t_swap	*last;

	first = *stack;
	if (!stack || !*stack || (*stack)->next == NULL)
		return (0);
	last = *stack;
	while (last->next)
		last = last->next;
	*stack = first->next;
	(*stack)->pre = NULL;
	last->next = first;
	first->pre = last;
	first->next = NULL;
	return (1);
}

void	rotate_ra(t_swap **stack_a)
{
	if (rotate_a_b(stack_a) == 1)
		write(1, "ra\n", 3);
}

void	rotate_rb(t_swap **stack_b)
{
	if (rotate_a_b(stack_b) == 1)
		write(1, "rb\n", 3);
}

void	rotate_rr(t_swap **stack_a, t_swap **stack_b)
{
	int	check_a;
	int	check_b;

	check_a = rotate_a_b(stack_a);
	check_b = rotate_a_b(stack_b);
	if (check_a == 1 || check_b == 1)
		write(1, "rr\n", 3);
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
        // デバッグ用：双方向の繋がりが壊れていないかチェック
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
    printf("【Before Rotate】\n");
    printf("Stack A: ");
    print_stack_debug(stack_a);
    printf("----------------------------------------\n\n");

    // 3. ra を実行（先頭の [1] を一番後ろへシフト！）
    // 引数には、先頭ポインタ変数の住所「&stack_a」を渡します
    rotate_ra(&stack_a);

    // 実行後の状態を表示
    printf("\n【After ra】\n");
    printf("Stack A: ");
    print_stack_debug(stack_a);
    printf("----------------------------------------\n");

    return (0);
}
*/
