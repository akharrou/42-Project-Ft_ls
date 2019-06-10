/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:08:16 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 12:05:45 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

uint64_t		get_flags(int *argc, const char **argv[])
{
	uint64_t	flags;
	size_t		i;
	size_t		j;
	size_t		k;

	flags = 0;
	i = 0;
	while ((*argv)[i] && (*argv)[i][0] == '-' && (*argv)[i][1] != '\0')
	{
		j = 0;
		while ((*argv)[i][++j] != '\0')
		{
			k = 0;
			while (g_flags[k].symbol && g_flags[k].symbol != (*argv)[i][j])
				++k;
			if (g_flags[k].symbol != '\0')
				flags |= g_flags[k].value;
			else
				EXIT(unknown_flag((*argv)[i][j]));
		}
		++i;
	}
	(*argv) += i;
	(*argc) -= (i + 1);
	return (flags);
}

void			*get_cmpft(uint64_t flags)
{
	if (flags & a_FLAG)
		flags ^= a_FLAG;
	if (flags & SORT_FLAG)
	{
		if (flags & f_FLAG)
		{
			return ((void *)&compare_by_none);
		}
		else if (flags & S_FLAG)
		{
			return ((void *)(flags & r_FLAG) ?
				&reverse_compare_by_size : &compare_by_size);
		}
		else if (flags & t_FLAG)
		{
			return ((void *)(flags & r_FLAG) ?
				&reverse_compare_by_time : &compare_by_time);
		}
	}
	return ((void *)(flags & r_FLAG) ?
		&reverse_compare_by_ascii : &compare_by_ascii);
}
