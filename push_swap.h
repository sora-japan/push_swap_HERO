/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/22 19:07:08 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/06/25 01:27:23 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

typedef struct s_swap
{
	int				num;
	int				rank;
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
void				simple_algorithm(t_swap **a, t_swap **b);
int					stack_size(t_swap *stack);
void				chunk_rank(t_swap *a);
void				bring_chunk(t_swap **a, t_swap **b, int chunk_size);
void				pull_from_b(t_swap **a, t_swap **b);
void				medium_algorithm(t_swap **a, t_swap **b);


double				calculate_disorder_fast(int a[], int n);
int					disorder_flg(double n);
int					ft_strcmp(char *s1, char *s2);

# include "libft/libft.h"

#endif
