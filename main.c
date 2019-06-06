/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:23:20 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 18:12:15 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int ac, const char *av[])
{
	int			(*cmpft)(void *, void *);
	uint64_t	flags;

	++av;
	flags = get_flags(&ac, &av);
	cmpft = (int (*)(void *, void *))get_cmpft(flags);
	ft_ls(ac, av, flags, cmpft);
	return (0);
}

/*
** Did the following bonuses: u, c, S, f, i, p
*/
