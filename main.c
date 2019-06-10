/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:23:20 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/09 20:54:40 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int ac, const char *av[])
{
	int			(*cmpft)(const void *, const void *);
	uint64_t	flags;

	++av;
	flags = get_flags(&ac, &av);
	cmpft = (int (*)(const void *, const void *))get_cmpft(flags);
	ft_ls(ac, av, flags, cmpft);
	sleep(1);
	return (0);
}
