/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 23:57:25 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 12:46:39 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int			compare_by_time(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)b)->time.tv_sec - (*(t_file **)a)->time.tv_sec;
	if (ret == 0)
	{
		ret = (*(t_file **)b)->time.tv_nsec - (*(t_file **)a)->time.tv_nsec;
		if (ret == 0)
			return (compare_by_ascii(a, b));
	}
	return (ret);
}

int			reverse_compare_by_time(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)a)->time.tv_sec - (*(t_file **)b)->time.tv_sec;
	if (ret == 0)
	{
		ret = (*(t_file **)a)->time.tv_nsec - (*(t_file **)b)->time.tv_nsec;
		if (ret == 0)
			return (reverse_compare_by_ascii(a, b));
	}
	return (ret);
}
