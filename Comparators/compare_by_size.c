/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:07:30 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 13:20:38 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_size(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)b)->size - (*(t_file **)a)->size;
	if (ret == 0)
		return (compare_by_ascii(a, b));
	return (ret);
}

int		reverse_compare_by_size(const void *a, const void *b)
{
	return (-(compare_by_size(a, b)));
}
