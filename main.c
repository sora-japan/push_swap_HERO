/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/20 14:17:46 by htakumi          ###   ########.fr       */
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

int	main(int ac, char **av)
{
	int		op;
	int		check;
	t_swap	*head;
	t_swap	*tmp;

	// char		**p;
	// t_swap	*a;
	// t_swap	b;
	// t_swap *tail;
	// t_swap *node;
	// char **p_start; // ft_splitの戻り値の先頭(後でfree)
	// a = NULL;
	if (ac == 1)
		return (0);
	else if (ac != 2 && ac != 3)
	{
		write(2, "1: Error\n", 9);
		return (0);
	}
	// option
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
	printf("check: %d", check);
	if (check == 0)
	{
		write(2, "3: Error\n", 9);
		return (0);
	}
	// stack
	head = stack_init(*av);
	tmp = head;
	while (tmp)
	{
		printf("%d\n", tmp->num);
		tmp = tmp->next;
	}
	// while (*p)
	// {
	// 	a = malloc(sizeof(t_swap));
	// 	a.num = ft_atoi(*p);
	// 	p++;
	// }
	return (0);
}
