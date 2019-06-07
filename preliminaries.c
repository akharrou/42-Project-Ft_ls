/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preliminaries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 22:08:16 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 22:28:24 by akharrou         ###   ########.fr       */
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
	int			(*cmpft)(void *, void *);
	size_t		i;

	i = 0;
	cmpft = &compare_by_ascii;
	if (flags & SORT_FLAG)
		while (g_flags[i].symbol != '\0')
		{
			if (flags & g_flags[i].value)
			{
				cmpft = (flags & r_FLAG) ?
					g_flags[i].reverse_cmp_function :
					g_flags[i].cmp_function;
				break ;
			}
			++i;
		}
	return ((void *)cmpft);
}
