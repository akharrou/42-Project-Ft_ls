/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 23:57:25 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 15:27:02 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int			compare_by_time(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)a)->time - (*(t_file **)b)->time;
	if (ret == 0)
		return (compare_by_ascii(a, b));
	return (ret < 0);
}

int			reverse_compare_by_time(const void *a, const void *b)
{
	return (-(compare_by_time(a, b)));
}
