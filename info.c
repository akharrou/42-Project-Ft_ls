/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:43 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/04 22:04:19 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			ft_getdirfile(struct dirent *direntry)
{
	struct stat	filestat;
	t_file		file;
	int			ret;

	if ((ret = stat((*direntry).d_name, &filestat)) == -1)
		EXIT(perror(NULL));
	file = (t_file) {
		.type = (*direntry).d_type,
		.inode = filestat.st_ino,
		.device_id = filestat.st_rdev,
		.mode = filestat.st_mode,
		.owner = (*getpwuid(filestat.st_uid)).pw_name,
		.group = (*getgrgid(filestat.st_gid)).gr_name,
		.size = filestat.st_size,
		.nblocks = filestat.st_blocks,
		.nlinks = filestat.st_nlink,
		.access_time = filestat.st_atime,
		.modifi_time = filestat.st_mtime,
		.change_time = filestat.st_ctime
	};
	if (file.type == SYMBOLIC_LINK)
		readlink(file.path, file.linkpath, MAX_PATHLEN);
	ft_strncpy(file.path, (*direntry).d_name, MAX_PATHLEN);
	ft_strncpy(file.name, ft_strrchr((*direntry).d_name, '/'), MAX_NAMELEN);
	return (file);
}

void			*wrap_getdirfile(void *vector_element, va_list ap)
{
	t_file		*file;

	file = (t_file *)malloc(sizeof(t_file));
	(*file) = ft_getdirfile((struct dirent *)vector_element);
	(void)ap;
	return (file);
}

t_vector		ft_getdirfiles(const char dirname[MAX_PATHLEN + 1])
{
	t_vector	dir;

	dir = ft_getdirentries(dirname);
	dir.remap(&dir, &wrap_getdirfile);
	return (dir);
}
