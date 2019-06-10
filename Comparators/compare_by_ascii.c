/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_ascii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:05:56 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 11:24:36 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_ascii(const void *a, const void *b)
{
	return (ft_strcmp((*(t_file **)a)->name, (*(t_file **)b)->name));
}

int		reverse_compare_by_ascii(const void *a, const void *b)
{
	return (-(compare_by_ascii(a, b)));
}
