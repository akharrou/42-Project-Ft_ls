/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_mtime.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:06:23 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 16:01:34 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_mtime(void *a, void *b)
{
	return ((*(t_file **)a)->modifi_time > (*(t_file **)b)->modifi_time);
}

int		reverse_compare_by_mtime(void *a, void *b)
{
	return (-(compare_by_mtime(a, b)));
}
