/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:06 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/11 22:31:11 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			ft_listfile(char *path, uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	t_file		file;
	int			fd;

	path = ft_strdup(path);
	file = ft_getfile(path, flags);
	if (file.type == DIRECTORY)
		ft_listdir(path, flags, cmpft);
	else
	{
		ft_strncpy(file.name, file.path, MAX_PATHLEN);
		fd = open(file.path, O_RDONLY);
		if (fd >= 0)
			ft_printfile(file, flags, (int[2]){ft_strlen(file.owner),
				ft_strlen(file.group)}, (int[3]){ft_intlen(file.inode),
				ft_intlen(file.size), ft_intlen(file.nlinks)});
		else
			ft_printf("ft_ls: %s: %s", file.name, strerror(errno));
		close(fd);
	}
	free(path);
	return ;
}

void			ft_listdir(char *dirpath, uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	DIR			*dirdes;
	char		tmp[MAX_NAMELEN];
	t_vector	dir;

	if (!(dirpath = ft_strdup(dirpath)))
		EXIT(perror(NULL));
	ft_basename(tmp, (const char *)dirpath);
	if (!(dirdes = opendir(dirpath)))
		ft_printf("ft_ls: %s: %s\n", tmp, strerror(errno));
	else
	{
		closedir(dirdes);
		dirpath = ft_strappend(dirpath, "/", 1, 0);
		if ((dir = ft_getdirfiles(dirpath, flags)).vector)
		{
			ft_quicksort(dir.vector, dir.length, sizeof(void *), cmpft);
			ft_printdir(dir, flags);
			if (flags & R_FLAG)
				ft_listdirs(dir, flags, cmpft, RECURSIVE);
			vector.destructor(&dir);
		}
	}
	free(dirpath);
	return ;
}

void			ft_listdirs(t_vector files, uint64_t flags,
					int (*cmpft)(const void *, const void *),
					uint8_t options)
{
	size_t		listed_dirs;
	t_file		file;
	size_t		i;

	listed_dirs = 0;
	i = -1;
	while (++i < files.length)
	{
		file = *(t_file *)files.vector[i];
		if (file.type == DIRECTORY)
		{
			if ((!(options & PRINT_DOTTED) && !(flags & a_FLAG) &&
			file.name[0] == '.') || (!(options & PRINT_DOTTED) &&
			(flags & a_FLAG) && (ft_strcmp(file.name, ".") == 0 ||
			ft_strcmp(file.name, "..") == 0)))
				continue ;
			if ((options & RECURSIVE) ||
			((options & HAS_FILES) && listed_dirs == 0) || listed_dirs++ > 0)
				ft_printf("\n");
			ft_printf("%s:\n", file.path);
			ft_listdir(file.path, flags, cmpft);
		}
	}
}

void			ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(const void *, const void *))
{
	t_vector	files;
	int			res;

	if (argc == 0)
		ft_listdir(".", flags, cmpft);
	else if (argc == 1)
		ft_listfile((char *)*argv, flags, cmpft);
	else
	{
		files = vector.from(argv, (size_t)argc, sizeof(char *));
		files.free = &free;
		files.remap(&files, &wrap_getfile_from_argv, flags);
		ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
		print_errors(files);
		res = print_files(files, flags);
		if (!(flags & d_FLAG))
			ft_listdirs(files, flags, cmpft, PRINT_DOTTED | res);
		files.free = &free_file_element;
		vector.destructor(&files);
	}
	return ;
}
