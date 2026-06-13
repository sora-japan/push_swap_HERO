/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 11:24:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/13 13:08:40 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <unistd.h>

int select_option(char **av)
{
	if (ft_strcmp(*av, "--simple") == 0)
		return (1);
	if (ft_strcmp(*av, "--medium") == 0)
		return (2);
	if (ft_strcmp(*av, "--complex") == 0)
		return (3);
	if (ft_strcmp(*av, "--adaptive") == 0)
		return (4);
	if (ft_strcmp(*av, "--bench") == 0)
		return (5);
	return (0);
}
int check_duplicate(char **av)
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
	while (av[2][i])
	{
		if (av[2][i] != ' ')
		{
			c = (unsigned char) av[2][i];
			if (av[2][i] == '-')
			{
				i++;
				if (s[c] == 0)
					s[c] = 1;
				else if (s[c] == 1)
					return (0);
			}
			if (s[c] == 0)
				s[c] = 1;
			else if (s[c] == 1)
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		i;
	int		op;
	t_swap	a;
	t_swap	b;
	int check;

	i = 0;
	if (ac != 2 || ac != 3)
		return (0);
	av++;
	check = 0;
	if (ac == 2)
	{
		check = check_duplicate(av);
		if (check == 0)
		{
			write (2, "Error\n", 6);
			return (0);
		}
		while (**av != '\0')
		{
			if (**av != ' ')
			{
				a.num = (int)*av;
				write(1, *av, 1);
			}
			(*av)++;
		}
	}
	if (ac == 3)
	{
		// option
		op = select_option(*av);
		check = check_duplicate(av);
		if (check == 0)
		{
			write (2, "Error\n", 6);
			return (0);
		}
		if (op == 0)
			return (0);
		// number
		av++;
		while (**av != '\0')
		{
			if (**av != ' ')
			{
				a.num = (int)*av;
				write(1, *av, 1);
			}
			(*av)++;
		}
	}
	return (0);
}
