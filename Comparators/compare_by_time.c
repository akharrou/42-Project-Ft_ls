/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_time.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 23:57:25 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 14:07:48 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int			compare_by_time(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)b)->time - (*(t_file **)a)->time;
	if (ret == 0)
		ret = ft_strcmp((*(t_file **)a)->name, (*(t_file **)b)->name);
	return (ret);
}

int			reverse_compare_by_time(const void *a, const void *b)
{
	long	ret;

	ret = (*(t_file **)a)->time - (*(t_file **)b)->time;
	if (ret == 0)
		ret = ft_strcmp((*(t_file **)b)->name, (*(t_file **)a)->name);
	return (ret);
}
