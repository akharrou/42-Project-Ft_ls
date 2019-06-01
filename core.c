
/*
**  Ft_ls -- Core Function(s).
*/

#include "ft_ls.h"


/*
**    NAME
**         ft_listdir -- list all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
**             int (*cmpft)(void *, void *));
**
**    PARAMETERS
**
**         const char dirname[MAX_PATHLEN]      Name of directory.
**
**         uint64_t flags                   Brief
**
**         int (*cmpft)(void *, void *)     Brief
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

int			ft_listdir(const char dirname[MAX_PATHLEN], uint64_t flags,
				int (*cmpft)(void *, void *))
{
	t_vector	dirfiles;
	size_t		i;

	dirfiles = ft_getdirfiles(dirname);
	if (!dirfiles.vector)
		return (-1);
	ft_quicksort(
		dirfiles.vector, dirfiles.length, sizeof(void *), cmpft);
	ft_printdir(dirfiles, flags);
	if (flags & RR_FLAG)
		dirfiles.viter(&dirfiles, &vprint_directories, 2, flags, cmpft);
	vector.destructor(&dirfiles);
	return (0);
}

/*
**    NAME
**         ft_ls -- equivalent to the 'ls' system command
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         ft_ls(int argc, const char *argv[], uint64_t flags,
**             int (*cmpft)(void *, void *));
**
**    PARAMETERS
**
**         int ac                           Argument count.
**
**         const char *av[]                 Argument vector.
**
**         uint64_t flags                   Flags.
**
**         int (*cmpft)(void *, void *)     Comparasion function
**                                          used to sort the entries
**                                          of a directory.
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

int				ft_ls(int argc, const char *argv[], uint64_t flags,
					int (*cmpft)(void *, void *))
{
	t_vector	files;
	size_t		i;

	if (argv == NULL || cmpft == NULL)
		return (-1);
	if (argc == 0)
		return (ft_listdir(".", flags, cmpft));
	if (argc == 1)
		return (ft_listdir(argv[1], flags, cmpft));
	files = vector.map(argv, (size_t)argc, sizeof(char *), &/* TODO */);
	ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
	files.iter(&files, &print_errors);
	files.iter(&files, &print_files);
	files.viter(&files, &vprint_directories, argc, flags, cmpft);
	vector.destructor(&files);
	return (0);
}
