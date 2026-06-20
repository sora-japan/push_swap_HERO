/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/20 16:41:13 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	select_option(char *av)
{
	if (ft_strcmp(av, "--simple") == 0)
		return (1);
	if (ft_strcmp(av, "--medium") == 0)
		return (2);
	if (ft_strcmp(av, "--complex") == 0)
		return (3);
	if (ft_strcmp(av, "--adaptive") == 0)
		return (4);
	if (ft_strcmp(av, "--bench") == 0)
		return (5);
	return (0);
}

int	is_valid_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
	{
		i++;
		if (str[i] == '\0')
			return (0);
	}
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_duplicate(char *av)
{
	char	**arr;
	int		i;
	int		j;
	int		k;

	arr = ft_split(av, ' ');
	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
	{
		if (!is_valid_number(arr[i]))
		{
			k = 0;
			while (arr[k])
				free(arr[k++]);
			free(arr);
			return (0);
		}
		j = i + 1;
		while (arr[j])
		{
			if (ft_atoi(arr[i]) == ft_atoi(arr[j]))
			{
				// freeしてから
				i = 0;
				while (arr[i])
					free(arr[i++]);
				free(arr);
				return (0);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
	return (1);
}

t_swap	*stack_init(char *str)
{
	char	**p_start;
	char	**p;
	t_swap	*head;
	t_swap	*tail;
	t_swap	*node;

	p_start = ft_split(str, ' ');
	if (p_start == NULL)
		return (NULL);
	p = p_start;
	head = NULL;
	tail = NULL;
	while (*p != NULL)
	{
		node = malloc(sizeof(t_swap));
		if (!node)
			return (NULL);
		node->num = ft_atoi(*p);
		node->next = NULL;
		node->pre = tail;
		if (tail != NULL)
			tail->next = node;
		if (head == NULL)
			head = node;
		tail = node;
		free(*p);
		p++;
	}
	free(p_start);
	return (head);
}

//STAGE 2：ヘルパー関数①「スタックのサイズを求める」 ループの回数（n-2回）を決めるためにサイズが必要です。

static int stack_size(t_swap *stack)
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

// STAGE 3：ヘルパー関数②「最小値のインデックスを求める」 スタックの先頭を index=0 として、最小値が何番目にあるかを返します。
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

// STAGE 4：最小値を先頭に持ってくる インデックスとサイズをもとに、どちら向きに回転するか決めます。
// 最小値を先頭に持ってくる
static void	bring_min_to_top(t_swap **a, int min_index, int size)
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

int	main(int ac, char **av)
{
	int		op;
	int		check;
	t_swap	*head;
	// t_swap	*tmp;
	t_swap *b;
	
	// char		**p;
	// t_swap	*a;
	// t_swap	b;
	// t_swap *tail;
	// t_swap *node;
	// char **p_start; // ft_splitの戻り値の先頭(後でfree)
	// a = NULL;
	op = 0;
	if (ac == 1)
		return (0);
	else if (ac != 2 && ac != 3)
	{
		write(2, "1: Error\n", 9);
		return (0);
	}
	// option
	b = NULL;
	if (ac == 3)
	{
		av++;
		op = select_option(*av);
		if (op == 0)
		{
			write(2, "2: Error\n", 9);
			return (0);
		}
	}
	av++;
	// number check
	check = check_duplicate(*av);
	// printf("check: %d", check);
	if (check == 0)
	{
		write(2, "3: Error\n", 9);
		return (0);
	}
	// stack
	head = stack_init(*av);
	if (op == 1)
		simple_algorithm(&head, &b);
	// tmp = head;
	//while (tmp)
	//{
		// printf("%d\n", tmp->num);
	//	tmp = tmp->next;
	//}
	// while (*p)
	// {
	// 	a = malloc(sizeof(t_swap));
	// 	a.num = ft_atoi(*p);
	// 	p++;
	// }
	return (0);
}
