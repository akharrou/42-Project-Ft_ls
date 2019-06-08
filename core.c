/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 17:34:10 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			ft_listfile(char *path, uint64_t flags,
				int (*cmpft)(void *, void *))
{
	t_file	file;

	file = ft_getfile(path, flags);
	if (!(flags & l_FLAG) || (flags & L_FLAG) || file.type == DIRECTORY)
	{
		ft_printf("%s:\n", path);
		return (ft_listdir(ft_strdup(path), flags, cmpft));
	}
	else
		ft_printfile(file, flags, (int[2]){ft_strlen(file.owner),
			ft_strlen(file.group)}, (int[3]){ft_intlen(file.inode),
			ft_intlen(file.size), ft_intlen(file.nlinks)});
	return (0);
}

int				ft_listdir(char *dirpath, uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	dir;

	if (!opendir(dirpath))
		ft_printf("ft_ls: %s: %s\n", dirpath, strerror(errno));
	else
	{
		if (dirpath[ft_strlen(dirpath) - 1] != '/')
			dirpath = ft_strappend(dirpath, "/", 1, 0);
		dir = ft_getdirfiles(dirpath, flags);
	}
	if (dir.vector)
	{
		ft_quicksort(dir.vector, dir.length, sizeof(void *), cmpft);
		ft_printdir(dir, flags);
		if (flags & R_FLAG)
			ft_listdirs(dir, flags, cmpft);
		vector.destructor(&dir);
	}
	free(dirpath);
	return (0);
}

int				ft_listdirs(t_vector files, uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_file		*file;
	size_t		i;

	i = -1;
	while (++i < files.length)
	{
		file = (t_file *)files.vector[i];
		if (file->type == DIRECTORY)
		{
			if ((!(flags & a_FLAG) && file->name[0] == '.') ||
				ft_strcmp(file->name, ".") == 0 ||
				ft_strcmp(file->name, "..") == 0)
			{
				continue ;
			}
			ft_printf("\n%s:\n", file->path);
			if (ft_listdir(ft_strdup(file->path), flags, cmpft) == -1)
				return (-1);
		}
	}
	return (0);
}

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;

	if (argc == 0)
		return (ft_listdir(ft_strdup("."), flags, cmpft));
	else if (argc == 1)
		return (ft_listfile((char *)*argv, flags, cmpft));
	else
	{
		files = vector.from(argv, (size_t)argc, sizeof(char *));
		files.free = &free;
		files.remap(&files, &wrap_getfile_from_argv, flags);
		ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
		files.iter(&files, &print_errors);
		files.viter(&files, &vprint_files, flags);
		ft_listdirs(files, flags, cmpft);
		files.free = &free_file_element;
		vector.destructor(&files);
	}
	return (0);
}
