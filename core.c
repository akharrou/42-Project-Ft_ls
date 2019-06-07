/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 03:04:55 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
	(void)flags;
	if (dir.vector)
	{
		ft_quicksort(dir.vector, dir.length, sizeof(void *), cmpft);
		ft_printdir(dir, flags);
		if (flags & R_FLAG)
			dir.viter(&dir, &vprint_dirs, 2, dirpath, flags, cmpft);
		vector.destructor(&dir);
	}
	free(dirpath);
	return (0);
}

static void		*wrap_getfile_from_argv(void *vector_element, va_list ap)
{
	const char	*path;
	uint64_t	flags;
	t_file		*file;

	flags = va_arg(ap, uint64_t);
	path = (*(const char **)vector_element);
	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getfile(path, flags);
	return (file);
}

void			ft_printdirs(t_vector files, uint64_t flags,
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
			ft_printf("\n%s:\n", file->name);
			ft_listdir(ft_strdup(file->path), flags, cmpft);
		}
	}
}

void			vprint_dirs(void *vector_element, va_list ap)
{
	int			(*cmpft)(void *, void *);
	char		*dirpath;
	uint64_t	flags;
	t_file		*file;

	if (!vector_element)
		return ;
	dirpath = va_arg(ap, char *);
	flags = va_arg(ap, uint64_t);
	cmpft = va_arg(ap, int (*)(void *, void *));
	file = (t_file *)vector_element;
	if ((!(flags & a_FLAG) && file->name[0] == '.') ||
		ft_strcmp(file->name, ".") == 0 ||
		ft_strcmp(file->name, "..") == 0)
	{
		return ;
	}
	if (file->type == DIRECTORY)
	{
		ft_printf("\n%s%s:\n", dirpath, file->name);
		ft_listdir(ft_vstrjoin(dirpath, 2, file->name, "/"), flags, cmpft);
	}
}

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;
	t_file		file;

	if (!argc)
		return (ft_listdir(ft_strdup("."), flags, cmpft));
	if (argc == 1)
	{
		file = ft_getfile(*argv, flags);
		if (!(flags & l_FLAG) || (flags & L_FLAG) || file.type == DIRECTORY)
		{
			(argc > 1) ? ft_printf("%s:\n", *argv) : PASS;
			ft_listdir(ft_strdup(*argv), flags, cmpft);
		}
		else
			ft_printfile(file, flags, (int[2]){ft_strlen(file.owner),
				ft_strlen(file.group)}, (int[3]){ft_intlen(file.inode),
				ft_intlen(file.size), ft_intlen(file.nlinks)});
	}
	else
	{
		files = vector.from(argv, (size_t)argc, sizeof(char *));
		files.remap(&files, &wrap_getfile_from_argv, flags);
		ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
		files.iter(&files, &print_errors);
		files.viter(&files, &vprint_files, flags);
		ft_printdirs(files, flags, cmpft);
		vector.destructor(&files);
	}
	return (0);
}
