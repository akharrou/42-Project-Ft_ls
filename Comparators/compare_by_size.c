/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_by_size.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:07:30 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/04 22:07:31 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_ls.h"

int		compare_by_size(void *a, void *b)
{
	return (((t_file *)a)->size - ((t_file *)b)->size);
}

int		reverse_compare_by_size(void *a, void *b)
{
	return (-(compare_by_size(a, b)));
}
