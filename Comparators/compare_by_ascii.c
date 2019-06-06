/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_ascii.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:05:56 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 02:53:32 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_ascii(void *a, void *b)
{
	return (
		ft_strcmp((*(t_file **)a)->name, (*(t_file **)b)->name));
}

int		reverse_compare_by_ascii(void *a, void *b)
{
	return (-(compare_by_ascii(a, b)));
}
