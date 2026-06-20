/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:07:08 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/20 16:01:24 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_swap
{
	int				num;
	struct s_swap	*pre;
	struct s_swap	*next;

}					t_swap;

void				swap_sa(t_swap *node);
void				swap_sb(t_swap *node);
void				swap_ss(t_swap *node_a, t_swap *node_b);
void				push_pa(t_swap **stack_a, t_swap **stack_b);
void				push_pb(t_swap **stack_a, t_swap **stack_b);
void				rotate_ra(t_swap **stack_a);
void				rotate_rb(t_swap **stack_b);
void				rotate_rr(t_swap **stack_a, t_swap **stack_b);
void    			rev_rotate_a(t_swap **stack_a);
void    			rev_rotate_b(t_swap **stack_b);
void    			rev_rotate_r(t_swap **stack_a, t_swap **stack_b);



double				calculate_disorder_fast(int a[], int n);
int					disorder_flg(double n);
int					ft_strcmp(char *s1, char *s2);

# include "libft/libft.h"

#endif
