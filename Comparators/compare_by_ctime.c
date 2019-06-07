/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_ctime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:05:56 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 22:09:41 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_ctime(void *a, void *b)
{
	long	res;

	res = ((*(t_file **)a)->change_time - (*(t_file **)b)->change_time);
	if (res == 0)
		return (0);
	return ((res < 0) ? 1 : -1);
}

int		reverse_compare_by_ctime(void *a, void *b)
{
	return (-(compare_by_ctime(a, b)));
}
