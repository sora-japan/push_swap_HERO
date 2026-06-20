/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/13 16:22:42 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <unistd.h>

int select_option(char *av)
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
int check_duplicate(char *av)
{
    int i;
    char s[256];
    unsigned char c;

	i = 0;
    while (i < 256)
    {
        s[i] = 0;
        i++;
    }
	i = 0;
	while (av[i] != '\0')
	{
		if (av[i] == ' ')
		{
			i++;
			continue;
		}
		if (av[i] == '-')
		{
			i++;
			c = (unsigned char) av[i];
			if (s[c] == 0)
				s[c] = 1;
			else if (s[c] == 1)
				return (0);
			i++;
			continue;
		}
		if (!(av[i] >= '0' && av[i] <= '9'))
			return (0);
		c = (unsigned char) av[i];
		if (s[c] == 0)
			s[c] = 1;
		else if (s[c] == 1)
			return (0);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		op;
	char		**p;
	t_swap	*a;
	// t_swap	b;
	int check;

	a = NULL;
	if (ac == 1)
		return (0);
	else if (ac != 2 && ac != 3)
	{
		write (2, "1: Error\n", 9);
		return (0);
	}

	// option
	if (ac == 3)
	{
		av++;
		op = select_option(*av);
		if (op == 0)
		{
			write (2, "2: Error\n", 9);
			return (0);
		}
	}
	av++;
	//number check
	check = check_duplicate(*av);
	printf("check: %d", check);
	if (check == 0)
	{
		write (2, "3: Error\n", 9);
		return (0);
	}
	// stack
	p = ft_split(*av, ' ');
	if (p == NULL)
		return (0);
	while (*p)
	{
		a = malloc(sizeof(t_swap));
		a.num = ft_atoi(*p);
		p++;
	}
	
	return (0);
}

a.num = (int)*av;
a.pre = NULL;
a.next = &a2;

while (**av != '\0')
{
	a.num = (int)*av;
	a.next->pre
}

ft_split(*av, ' ');