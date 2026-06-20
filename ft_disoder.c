/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disoder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 15:17:28 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/06/20 14:35:55 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static long long	merge_and_count(int arr[], int temp[], int left, int mid, int right)
{
	int			i;
	int			j;
	int			k;
	long long	inversions;

	i = left;
	j = mid + 1;
	k = left;
	inversions = 0;
	while (i <= mid && j <= right)
	{
		if (arr[i] <= arr[j])
		{
			temp[k] = arr[i];
			i++;
		}
		else
		{
			temp[k] = arr[j];
			j++;
			inversions += (mid - i + 1);
		}
		k++;
	}
	while (i <= mid)
	{
		temp[k] = arr[i];
		i++;
		k++;
	}
	while (j <= right)
	{
		temp[k] = arr[j];
		j++;
		k++;
	}
	i = left;
	while (i <= right)
	{
		arr[i] = temp[i];
		i++;
	}
	return (inversions);
}

static long long	merge_sort_and_count(int arr[], int temp[], int left, int right)
{
	long long	inversions;
	int			mid;

	inversions = 0;
	if (left < right)
	{
		mid = left + (right - left) / 2;
		inversions += merge_sort_and_count(arr, temp, left, mid);
		inversions += merge_sort_and_count(arr, temp, mid + 1, right);
		inversions += merge_and_count(arr, temp, left, mid, right);
	}
	return (inversions);
}

double	calculate_disorder_fast(int a[], int n)
{
	double		total_pairs;
	int			*arr_copy;
	int			*temp;
	long long	mistakes;
	int			i;

	if (n <= 1)
		return (0.0);
	total_pairs = (double)n * (n - 1) / 2.0;
	arr_copy = (int *)malloc(n * sizeof(int));
	if (!arr_copy)
		return (0.0);
	i = 0;
	while (i < n)
	{
		arr_copy[i] = a[i];
		i++;
	}
	temp = (int *)malloc(n * sizeof(int));
	if (!temp)
	{
		free(arr_copy);
		return (0.0);
	}
	mistakes = merge_sort_and_count(arr_copy, temp, 0, n - 1);
	free(arr_copy);
	free(temp);
	return ((double)mistakes / total_pairs);
}

int disorder_flg(double n)
{
    if (n < 0.2)
        return (1);
    if (0.2 <= n && n < 0.5)
        return (2);
    if (n >= 0.5)
        return (3);
    return (0);
    // 0.2 未満（ほぼソート済み）	O(n²)
    // 0.2 以上 0.5 未満	O(n√n)
    // 0.5 以上（かなり乱れている）	O(n log n)
}

// int	main(void)
// {
// 	int		array[8];
// 	int		n;
// 	int		flg;
// 	double	disorder;

// 	array[0] = 1;
// 	array[1] = 2;
// 	array[2] = 4;
// 	array[3] = 3;


// 	n = 4;
// 	disorder = calculate_disorder_fast(array, n);
// 	flg = disorder_flg(disorder);
// 	printf("不整合度 (Disorder): %.4f\n", disorder);
// 	printf("オプション: %d\n", flg);
// 	return (0);
// }
