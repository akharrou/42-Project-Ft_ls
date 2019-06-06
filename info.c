/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:43 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/05 20:19:39 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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
		.change_time = filestat.st_ctime
	};
	ft_strncpy(file.path, path, MAX_PATHLEN);
	tmp = ft_strrchr(path, '/');
	ft_strncpy(file.name, ((tmp != NULL) ? tmp + 1 : path), MAX_NAMELEN);
	if (file.type == SYMBOLIC_LINK)
		readlink(file.path, file.linkpath, MAX_PATHLEN);
	return (file);
}

t_vector		ft_getdirfiles(const char dirpath[MAX_PATHLEN + 1])
{
	t_vector	dir;

	dir = ft_getdirentries(dirpath);
	if (dir.vector != NULL)
		dir.remap(&dir, &wrap_getfile_from_dirent);
	return (dir);
}
