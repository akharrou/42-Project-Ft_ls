/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:43 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/06 04:35:24 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static mode_t	mode2type(mode_t mode)
{
	mode_t		type;

	if (S_ISREG(mode))
		type = REGULAR_FILE;
	else if (S_ISDIR(mode))
		type = DIRECTORY;
	else if (S_ISLNK(mode))
		type = SYMBOLIC_LINK;
	else if (S_ISFIFO(mode))
		type = NAMED_PIPE;
	else if (S_ISSOCK(mode))
		type = SOCKET;
	else if (S_ISCHR(mode))
		type = CHARACTER_FILE;
	else if (S_ISBLK(mode))
		type = BLOCK_FILE;
	else
		type = UNKNOWN_FILE;
	return (type);
}

t_file			ft_getfile(const char path[MAX_PATHLEN + 1])
{
	struct stat	filestat;
	t_file		file;
	char		*tmp;

	if (stat(path, &filestat) == -1)
		EXIT(perror(NULL));
	file = (t_file) {
		.type = mode2type(filestat.st_mode),
		.inode = filestat.st_ino,
		.device_id = filestat.st_rdev,
		.mode = filestat.st_mode,
		.owner = getpwuid(filestat.st_uid)->pw_name,
		.group = getgrgid(filestat.st_gid)->gr_name,
		.size = filestat.st_size,
		.nlinks = filestat.st_nlink,
		.nblocks = filestat.st_blocks,
		.access_time = filestat.st_atime,
		.modifi_time = filestat.st_mtime,
		.change_time = filestat.st_ctime };
	ft_strncpy(file.path, path, MAX_PATHLEN);
	tmp = ft_strrchr(path, '/');
	ft_strncpy(file.name, ((tmp != NULL) ? tmp + 1 : path), MAX_NAMELEN);
	if (file.type == SYMBOLIC_LINK)
		readlink(file.path, file.linkpath, MAX_PATHLEN);
	return (file);
}

static void		*wrap_getfile_from_dirent(void *vector_element, va_list ap)
{
	t_file		*file;
	char		*path;

	path = va_arg(ap, char *);
	path = ft_strdup(path);
	file = (t_file *)malloc(sizeof(t_file));
	path = ft_strjoin(path, ((struct dirent *)vector_element)->d_name);
	(*file) = ft_getfile(path);
	free(path);
	return (file);
}

t_vector		ft_getdirfiles(const char dirpath[MAX_PATHLEN + 1])
{
	t_vector	dir;

	dir = ft_getdirentries(dirpath);
	if (dir.vector != NULL)
		dir.remap(&dir, &wrap_getfile_from_dirent, dirpath);
	return (dir);
}
