/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/10 12:27:05 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				ft_listfile(char *path, uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	t_file		file;
	int			ret;
	int			fd;

	ret = 0;
	path = ft_strdup(path);
	file = ft_getfile(path, flags);
	if (file.type == DIRECTORY)
		ret = ft_listdir(path, flags, cmpft);
	else
	{
		fd = open(file.path, O_RDONLY);
		if (fd >= 0)
			ft_printfile(file, flags, (int[2]){ft_strlen(file.owner),
				ft_strlen(file.group)}, (int[3]){ft_intlen(file.inode),
				ft_intlen(file.size), ft_intlen(file.nlinks)});
		else
			ft_printf("ft_ls: %s: %s\n", path, strerror(errno));
		close(fd);
	}
	free(path);
	return (ret);
}

int				ft_listdir(char *dirpath, uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	DIR			*dirdes;
	t_vector	dir;
	int			ret;

	ret = -1;
	if (!(dirpath = ft_strdup(dirpath)))
		return (-1);
	if (!(dirdes = opendir(dirpath)))
		ft_printf("ft_ls: %s: %s\n", dirpath, strerror(errno));
	else
	{
		closedir(dirdes);
		if (dirpath[ft_strlen(dirpath) - 1] != '/')
			dirpath = ft_strappend(dirpath, "/", 1, 0);
		if ((dir = ft_getdirfiles(dirpath, flags)).vector)
		{
			ft_quicksort(dir.vector, dir.length, sizeof(void *), cmpft);
			ret = ft_printdir(dir, flags);
			if (flags & R_FLAG)
				ret = ft_listdirs(dir, flags, cmpft, NO_PRINT_DOTTED);
			vector.destructor(&dir);
		}
	}
	free(dirpath);
	return (ret);
}

int				ft_listdirs(t_vector files, uint64_t flags,
					int (*cmpft)(const void *, const void *),
					uint8_t options)
{
	int			first;
	t_file		file;
	size_t		i;

	first = 1;
	i = -1;
	while (++i < files.length)
	{
		file = *(t_file *)files.vector[i];
		if (file.type == DIRECTORY)
		{
			if (first-- == 1 && (PRINT_NEWLINE & options))
				ft_printf("\n");
			if (!(PRINT_DOTTED & options) && !(flags & a_FLAG) &&
				file.name[0] == '.')
				continue ;
			if (!(PRINT_DOTTED & options) && (flags & a_FLAG) &&
			(ft_strcmp(file.name, ".") == 0 || ft_strcmp(file.name, "..") == 0))
				continue ;
			ft_printf("%s:\n", file.path);
			if (ft_listdir(file.path, flags, cmpft) == -1)
				return (-1);
		}
	}
	return (0);
}

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	t_vector	files;
	int			res;

	if (argc == 0)
		return (ft_listdir(".", flags, cmpft));
	else if (argc == 1)
		return (ft_listfile((char *)*argv, flags, cmpft));
	else
	{
		files = vector.from(argv, (size_t)argc, sizeof(char *));
		files.free = &free;
		files.remap(&files, &wrap_getfile_from_argv, flags);
		ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
		print_errors(files);
		res = print_files(files, flags);
		ft_listdirs(files, flags, cmpft, PRINT_DOTTED | res);
		files.free = &free_file_element;
		vector.destructor(&files);
	}
	return (0);
}
