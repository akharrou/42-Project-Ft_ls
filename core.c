/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 19:11:57 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_listdir(char *dirpath, uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	dir;

	dir = ft_getdirfiles(dirpath);
	if (dir.vector)
	{
		ft_quicksort(dir.vector, dir.length, sizeof(void *), cmpft);
		ft_printdir(dir, flags);
		if (flags & R_FLAG)
		{
			dir.viter(&dir, &vprint_directories, dirpath, flags, cmpft);
		}
		vector.destructor(&dir);
	}
	free(dirpath);
	return (0);
}

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;

	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argc == 0)
		return (ft_listdir(ft_strdup("./"), flags, cmpft));
	if (argc == 1)
		return (ft_listdir(ft_strjoin(argv[1], "/"), flags, cmpft));
	files = vector.map(
		argv, (size_t)argc, sizeof(char *), &wrap_getfile_from_argv);
	ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
	files.iter(&files, &print_errors);
	files.iter(&files, &print_files);
	files.viter(&files, &vprint_directories, ft_strdup("./"), flags, cmpft);
	vector.destructor(&files);
	return (0);
}
