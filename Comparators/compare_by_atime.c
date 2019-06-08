/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_atime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:06:15 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 16:01:05 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_atime(void *a, void *b)
{
	return ((*(t_file **)a)->access_time > (*(t_file **)b)->access_time);
}

int		reverse_compare_by_atime(void *a, void *b)
{
	return (-(compare_by_atime(a, b)));
}
