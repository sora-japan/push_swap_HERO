/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_a_b.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:16:51 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/25 01:52:11 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <unistd.h>

static int	swap_a_b(t_swap *node)
{
	int	tmp;

	if (node == NULL || node->next == NULL)
		return (0);
	tmp = node->num;
	node->num = node->next->num;
	node->next->num = tmp;
	return (1);
}

void	swap_sa(t_swap *node)
{
	int	check;

	check = swap_a_b(node);
	if (check == 1)
		write(1, "sa\n", 3);
	return ;
}

void	swap_sb(t_swap *node)
{
	int	check;

	check = swap_a_b(node);
	if (check == 1)
		write(1, "sb\n", 3);
	return ;
}

void	swap_ss(t_swap *node_a, t_swap *node_b)
{
	int	check;

	check = 0;
	check += swap_a_b(node_a);
	check += swap_a_b(node_b);
	if (check >= 1)
		write(1, "ss\n", 3);
	return ;
}
/*
#include <stdio.h>

int	main(void)
{
	t_swap	n1;
	t_swap	n2;
	t_swap	n3;

	n1.num = 2;
	n1.pre = NULL;
	n1.next = &n2;
	n2.num = 1;
	n2.pre = &n1;
	n2.next = &n3;
	n3.num = 3;
	n3.pre = &n2;
	n3.next = NULL;
	printf("Before: %d, %d, %d\n", n1.num, n2.num, n3.num);
	swap_sa(&n1);
	swap_sa(&n1);
	printf("After : %d, %d, %d\n", n1.num, n2.num, n3.num);
	return (0);
}
*/
