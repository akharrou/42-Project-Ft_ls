/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:07:30 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 22:13:25 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_size(void *a, void *b)
{
	long long	res;

	res = ((*(t_file **)a)->size - (*(t_file **)b)->size);
	if (res == 0)
		return (0);
	return ((res < 0) ? 1 : -1);
}

int		reverse_compare_by_size(void *a, void *b)
{
	return (-(compare_by_size(a, b)));
}
