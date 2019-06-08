/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_ctime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:05:56 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 16:01:17 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_ctime(void *a, void *b)
{
	return ((*(t_file **)a)->change_time > (*(t_file **)b)->change_time);
}

int		reverse_compare_by_ctime(void *a, void *b)
{
	return (-(compare_by_ctime(a, b)));
}
