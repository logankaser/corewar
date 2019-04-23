/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:24:36 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/17 11:41:41 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	partition(void *array[], int lo, int hi,
	bool (*comp)(const void *, const void *))
{
	void	*pivot;
	int		i;
	int		j;
	void	*tmp;

	pivot = array[lo + (hi - lo) / 2];
	i = lo - 1;
	j = hi + 1;
	while (1)
	{
		++i;
		while (comp(pivot, array[i]))
			++i;
		--j;
		while (comp(array[j], pivot))
			--j;
		if (i >= j)
			return (j);
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

static void	sort(void *array[], int lo, int hi,
	bool (*comp)(const void *, const void *))
{
	int	p;

	if (lo < hi)
	{
		p = partition(array, lo, hi, comp);
		sort(array, lo, p, comp);
		sort(array, p + 1, hi, comp);
	}
}

void		ft_qsort(void *array[], int size,
	bool (*comp)(const void *, const void *))
{
	sort(array, 0, size - 1, comp);
}

bool		ft_compare_str_asc(const void *a, const void *b)
{
	return (ft_strcmp(a, b) > 0);
}

bool		ft_compare_int_asc(const void *a, const void *b)
{
	return (*((int*)a) > *((int*)b));
}
