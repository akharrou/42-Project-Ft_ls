
/*
**  Ft_ls -- Gather information about each file/directory
*/

#include "ft_ls.h"

t_file	ft_getdirfile(struct dirent file_entry)
{
	t_file	file;

	direntries = ft_getdirentries(dirname);
	file = (t_file) {
		.type = 0,
		.linked_to_path = 0,
		.time = 0,
		.size = 0,
		.group = 0,
		.owner = 0,
		.links = 0,
		.mode = 0
	};
	ft_strncpy(file.path, filepath, MAX_PATHLEN);
	ft_strncpy(file.name, ft_strrchr(filepath, '/'), MAX_NAMELEN);
	return (file);
}

t_vector	ft_getdirfiles(const char dirname[MAX_PATHLEN + 1])
{
	t_vector	dir;
	t_vector	dirfiles;

	dir = ft_getdirentries(dirname);
	dirfiles = vector.map(
		dir.vector, dir.length, sizeof(void *), &ft_getdirfile);
	/* create and fill in a t_file structure for each entry in the 'dir' vector and store it in a vector */
}
