/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:23:20 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 22:52:06 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void	print_elem(void *e)
// {
// 	ft_printf("%s\n", *(char **)e);
// }

// int		ft_strcmp_v(void *a, void *b)
// {
// 	int res;

// 	res = ft_strcmp(**(char ***)a, **(char ***)b);
// 	return (res);
// }

int				main(int ac, const char *av[])
{
	int			(*cmpft)(void *, void *);
	uint64_t	flags;

	++av;
	flags = get_flags(&ac, &av);
	cmpft = (int (*)(void *, void *))get_cmpft(flags);
	ft_ls(ac, av, flags, cmpft);

	// t_vector instance;

	// instance = vector.from(++av, --ac, sizeof(void *));

	// ft_printf("—————————————————————————————————————————————————————————\n");
	// ft_printf("Pre-Sort:\n\n");
	// instance.iter(&instance, &print_elem);

	// ft_quicksort(instance.vector, instance.length, sizeof(void *), &ft_strcmp_v);

	// ft_printf("—————————————————————————————————————————————————————————\n");
	// ft_printf("Post-Sort:\n\n");
	// instance.iter(&instance, &print_elem);

	// ft_printf("—————————————————————————————————————————————————————————\n");

	// (void)av;
	// (void)ac;

	return (0);
}
