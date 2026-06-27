/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/28 08:46:34 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *join_argv(char **av)
{
	int total;
	int i;
	char *result;

	i = 0;
	total = 0;
	while (av[i])
	{
		total += ft_strlen(av[i]) + 1;
		i++;
	}
	result = malloc(total + 1);
	if (!result)
		return (NULL);
	result[0] = '\0';
	i = 0;
	while (av[i])
	{
		ft_strlcat(result, av[i], total + 1);
		if (av[i + 1])
			ft_strlcat(result, " ", total + 1);
		i++;
	}
	return (result);
}

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
		node->rank = 0;
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

// ミディアムアルゴ

void	chunk_rank(t_swap *a)
{
	t_swap	*min_rank;
	t_swap	*cur;
	int		rank_count;

	min_rank = a;
	while (min_rank != NULL)
	{
		cur = a;
		rank_count = 0;
		while (cur != NULL)
		{
			if (cur->num < min_rank->num)
			{
				rank_count++;
			}
			cur = cur->next;
		}
		min_rank->rank = rank_count;
		min_rank = min_rank->next;
	}
}

// 　√nの計算
static int	chunk_size(t_swap *stack)
{
	int	n;
	int	i;

	n = stack_size(stack);
	i = 1;
	if (n <= 3)
		return (n);
	while (i * i <= n)
		i++;
	return (i - 1);
}
// 役割： 今のチャンク範囲に何個の要素があるかを数える
// なぜ必要か： bring_chunk の内ループを「あと何回 pb すれば終わりか」で管理するため。
static int	count_in_chunk(t_swap *a, int start, int end)
{
	int	count;

	count = 0;
	while (a != NULL)
	{
		if (a->rank >= start && a->rank < end)
			count++;
		a = a->next;
	}
	return (count);
}

// 役割： チャンク範囲内で一番近い要素が先頭から何番目にあるかを返す
// なぜ必要か： ra（前から回す）か rra（後ろから回す）かを判断するため。位置が size/2 以下なら ra、超えていれば rra が効率的。
static int	find_chunk_index(t_swap *a, int start, int end)
{
	int	j;

	j = 0;
	while (a != NULL)
	{
		if (a->rank >= start && a->rank < end)
			return (j);
		a = a->next;
		j++;
	}
	return (0);
}
// 役割： チャンクを0番から順に処理して、a の全要素を b に積む
void	bring_chunk(t_swap **a, t_swap **b, int chunk_size)
{
	int	chunk_start;
	int	chunk_end;
	int	count;

	chunk_start = 0;
	chunk_end = chunk_size;
	while (*a != NULL)
	{
		count = count_in_chunk(*a, chunk_start, chunk_end);
		while (count > 0)
		{
			if ((*a)->rank >= chunk_start && (*a)->rank < chunk_end)
			{
				push_pb(a, b);
				count--;
			}
			else if (find_chunk_index(*a, chunk_start,
					chunk_end) <= stack_size(*a) / 2)
				rotate_ra(a);
			else
				rev_rotate_a(a);
		}
		chunk_start = chunk_end;
		chunk_end += chunk_size;
	}
}

static int	find_max_rank_index(t_swap *b)
{
	int	max_rank;
	int	max_index;
	int	i;

	max_rank = b->rank;
	max_index = 0;
	i = 0;
	while (b != NULL)
	{
		if (b->rank > max_rank)
		{
			max_rank = b->rank;
			max_index = i;
		}
		b = b->next;
		i++;
	}
	return (max_index);
}

void	pull_from_b(t_swap **a, t_swap **b)
{
	int	max_idx;
	int	size;

	while (*b != NULL)
	{
		size = stack_size(*b);
		max_idx = find_max_rank_index(*b);
		if (max_idx <= size / 2)
		{
			while (max_idx-- > 0)
				rotate_rb(b);
		}
		else
		{
		    max_idx = size - max_idx;
    		while (max_idx-- > 0)
        		rev_rotate_b(b);
		}
		push_pa(a, b);
	}
}

void	medium_algorithm(t_swap **a, t_swap **b)
{
	int	n;

	chunk_rank(*a);       // STAGE 1: ランク付け
	n = chunk_size(*a);   // STAGE 2: チャンクサイズ
	bring_chunk(a, b, n); // STAGE 3: b に積む
	pull_from_b(a, b);    // STAGE 4: a に戻す ← 追加
}

int	main(int ac, char **av)
{
	int		op;
	int		check;
	t_swap	*head;
	t_swap	*b;
	char *join;

	// t_swap	*tmp;
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
//	else if (ac != 2 && ac != 3)
//	{
//		write(2, "1: Error\n", 9);
//		return (0);
//	}
	// option
	b = NULL;
	av++;
//	if (ac == 3)
//	{
//		av++;
//		op = select_option(*av);
//		if (op == 0)
//		{
//			write(2, "2: Error\n", 9);
//			return (0);
//		}
//	}
	if (select_option(*av) != 0)
	{
		op = select_option(*av);
		av++;
	}
	join = join_argv(av);
	if (!join)
		return (0);
	// number check
	check = check_duplicate(join);
	// printf("check: %d", check);
	if (check == 0)
	{
		free(join);
		write(2, "3: Error\n", 9);
		return (0);
	}
	// stack
	head = stack_init(join);
	free(join);
	if (op == 1)
		simple_algorithm(&head, &b);
	if (op == 2)
		medium_algorithm(&head, &b);
	// tmp = head;
	// while (tmp)
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
