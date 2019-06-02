/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/01 19:24:39 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	dir;

	dir = ft_getdirfiles(dirname);
	if (!dir.vector)
		return (-1);
	ft_quicksort(
		dir.vector, dir.length, sizeof(void *), cmpft);
	ft_printdir(dir, flags);
	if (flags & RR_FLAG)
		dir.viter(&dir, &vprint_directories, 2, flags, cmpft);
	vector.destructor(&dir);
	return (0);
}

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;

	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argc == 0)
		return (ft_listdir(".", flags, cmpft));
	if (argc == 1)
		return (ft_listdir(argv[1], flags, cmpft));

	/* GET T_FILE VECTOR FROM ARGV */
	files = vector.map(argv, (size_t)argc, sizeof(char *), &);

	ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
	files.iter(&files, &print_errors);
	files.iter(&files, &print_files);
	files.viter(&files, &vprint_directories, argc, flags, cmpft);
	vector.destructor(&files);
	return (0);
}
