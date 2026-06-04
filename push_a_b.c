/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 22:00:39 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/25 02:32:47 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "push_swap.h"

static int	push_a_b(t_swap **before, t_swap **after)
{
	t_swap	*before_node;

	if (before == NULL || *before == NULL)
		return (0);
	before_node = *before;
	*before = before_node->next;
	if (*before != NULL)
		(*before)->pre = NULL;
	before_node->next = *after;
	before_node->pre = NULL;
	if (*after != NULL)
		(*after)->pre = before_node;
	*after = before_node;
	return (1);
}

void	push_pa(t_swap **stack_a, t_swap **stack_b)
{
	int	check;

	check = push_a_b(stack_b, stack_a);
	if (check == 1)
		write(1, "pa\n", 3);
	return ;
}

void	push_pb(t_swap **stack_a, t_swap **stack_b)
{
	int	check;

	check = push_a_b(stack_a, stack_b);
	if (check == 1)
		write(1, "pb\n", 3);
	return ;
}
/*
#include <stdio.h>

// テスト用：スタックの状態を上から順番にプリントする関数
void    print_stacks(t_swap *stack_a, t_swap *stack_b)
{
    printf("--- Current Stacks ---\n");
    printf("Stack A: ");
    if (!stack_a)
        printf("(empty)");
    while (stack_a)
    {
        printf("[%d] ", stack_a->num);
        stack_a = stack_a->next;
    }
    printf("\nStack B: ");
    if (!stack_b)
        printf("(empty)");
    while (stack_b)
    {
        printf("[%d] ", stack_b->num);
        stack_b = stack_b->next;
    }
    printf("\n----------------------\n\n");
}

int main(void)
{
    // 1. スタックA用のノードを2つ作成
    t_swap a1, a2;
    a1.num = 1;
    a1.pre = NULL;
    a1.next = &a2;

    a2.num = 2;
    a2.pre = &a1;
    a2.next = NULL;

    // 2. スタックB用のノードを1つ作成
    t_swap b1;
    b1.num = 3;
    b1.pre = NULL;
    b1.next = NULL;

    // 3. 関数の外側にある「スタックの先頭を指すポインタ」を用意
    t_swap *stack_a = &a1;
    t_swap *stack_b = &b1;

    // 実行前の状態を表示
    printf("【Before Push】\n");
    print_stacks(stack_a, stack_b);

    // 4. pb を実行（Aの先頭 [1] を Bの先頭へプッシュ！）
    // 引数には、先頭ポインタ変数の住所（&stack_a, &stack_b）を渡します
    push_pb(&stack_a, &stack_b);

    // 実行後の状態を表示
    printf("\n【After pb】\n");
    print_stacks(stack_a, stack_b);

    return (0);
}
*/
