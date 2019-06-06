/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_mtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:06:23 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 02:55:56 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_mtime(void *a, void *b)
{
	long	res;

	res = ((*(t_file **)a)->modifi_time - (*(t_file **)b)->modifi_time);
	if (res == 0)
		return (0);
	return ((res > 0) ? 1 : -1);
}

int		reverse_compare_by_mtime(void *a, void *b)
{
	return (-(compare_by_mtime(a, b)));
}
