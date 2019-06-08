/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akharrou <akharrou@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 19:20:43 by akharrou          #+#    #+#             */
/*   Updated: 2019/06/07 20:47:32 by akharrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static mode_t		mode2type(mode_t mode)
{
	mode_t			type;

	if (S_ISREG(mode))
		type = REGULAR_FILE;
	else if (S_ISLNK(mode))
		type = SYMBOLIC_LINK;
	else if (S_ISDIR(mode))
		type = DIRECTORY;
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

t_file				ft_getfile(const char path[MAX_PATHLEN + 1], uint64_t flags)
{
	struct stat		filestat;
	t_file			file;

	ft_bzero(&filestat, sizeof(struct stat));
	(((flags & L_FLAG) || !(flags & l_FLAG)) ?
		stat(path, &filestat) : lstat(path, &filestat));
	file = (t_file) {
		.type = mode2type(filestat.st_mode),
		.inode = filestat.st_ino,
		.device_id = filestat.st_rdev,
		.mode = filestat.st_mode,
		.size = filestat.st_size,
		.nlinks = filestat.st_nlink,
		.nblocks = filestat.st_blocks,
		.access_time = filestat.st_atime,
		.modifi_time = filestat.st_mtime,
		.change_time = filestat.st_ctime
	};
	ft_strncpy(file.owner, getpwuid(filestat.st_uid)->pw_name, MAX_NAMELEN);
	ft_strncpy(file.group, getgrgid(filestat.st_gid)->gr_name, MAX_NAMELEN);
	ft_strncpy(file.path, path, MAX_PATHLEN);
	ft_basename(file.path, file.name);
	if (file.type == SYMBOLIC_LINK)
		readlink(file.path, file.linkpath, MAX_PATHLEN);
	return (file);
}

t_vector			ft_getdirfiles(char dirpath[MAX_PATHLEN + 1],
						uint64_t flags)
{
	char			pathcpy[MAX_PATHLEN + 1];
	struct dirent	*dirent;
	DIR				*dirdes;
	t_file			*file;
	t_vector		dir;

	errno = 0;
	dir = vector.empty(NULL);
	dir.free = &free_file_element;
	if ((dirdes = opendir(dirpath)) != NULL)
		while (errno == 0 && (dirent = readdir(dirdes)) != NULL)
		{
			if (!(file = (t_file *)malloc(sizeof(t_file))))
				EXIT(perror(NULL); dir.clear(&dir); closedir(dirdes));
			ft_vstrncpy(pathcpy, MAX_PATHLEN, 2, dirpath, dirent->d_name);
			(*file) = ft_getfile(pathcpy, flags);
			dir.append(&dir, file);
		}
	if (errno != 0)
	{
		perror(NULL);
		dir.clear(&dir);
	}
	closedir(dirdes);
	return (dir);
}
