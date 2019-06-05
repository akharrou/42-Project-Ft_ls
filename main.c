/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:23:20 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/04 21:48:14 by akharrou         ###   ########.fr       */
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
**
**  TODO :
**
**  Done [_]  ;  Reviewed [_]  ;            3 - must check if we have permissions before recursing down     / Need to know how the file will expand
**  Done [_]  ;  Reviewed [_]  ;            4 - must exclude '.' & '..' from recursive calling
**  Done [_]  ;  Reviewed [_]  ;  Aymen     6 - implement the vector.filter constructor
**  Done [_]  ;  Reviewed [_]  ;            7 - implement the printing function for a vector containing all files/directories
*/

/*

	TODO : implement the following functions/methods:

	vec_instance = vector.filter((void *)iterable, length, width, filter_ft);

	n = files.count(&files, &ft_isdirectory);
	n = files.find(&files, &ft_isdirectory);
*/

