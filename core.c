
/*
**  Ft_ls -- Core Function(s).
*/

#include "ft_ls.h"

/*
**    NAME
**         ft_getdir -- get all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         t_vector
**         ft_getdir(struct s_vector *self);
**
**    PARAMETERS
**
**         const char dirname[PATHMAX]      Name of directory.
**
**    DESCRIPTION
**         (not done); get a vector containing all the directory entries of
**         the 'dirname' directory
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

t_vector	ft_getdirentries(const char dirpath[PATHMAX + 1]);
{
	t_vector	result;
	DIR			*dirdes;

	result = vector.empty(NULL);
	dirdes = opendir(dirpath);
	if (dirdes != NULL)
	{

	}
	else
		perror();
	return (result);
}

/*
**    NAME
**         func_name -- brief
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         func_name(struct s_vector *self);
**
**    PARAMETERS
**
**         struct s_vector *self     Pointer to a vector instance.
**
**         void *data                Pointer to some data.
**
**         PARAM 3          Brief
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

void			ft_printdir(t_vector directory, uint64_t flags)
{
	int			links_width;
	int			size_width;
	size_t		i;

	size_width = 0;
	links_width = 0;
	i = 0;
	while (i < directory.length)
	{
		links_width = MAX(
			links_width, ft_intlen(((t_file *)directory.vector[i])->links));
		size_width = MAX(
			size_width, ft_intlen(((t_file *)directory.vector[i])->size));
		++i;
	}
	directory.viter(&directory, &ft_vprintfile, flags, links_width, size_width);
	return ;
}

/*
**    NAME
**         ft_listdir -- list all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         int
**         ft_listdir(const char dirname[PATHMAX], uint64_t flags,
**             int (*cmpft)(void *, void *));
**
**    PARAMETERS
**
**         const char dirname[PATHMAX]      Name of directory.
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

int			ft_listdir(const char dirname[PATHMAX], uint64_t flags,
				int (*cmpft)(void *, void *))
{
	t_vector	directory;
	size_t		i;

	directory = ft_getdirentries(dirname);
	if (!directory.vector)
		return (-1);
	ft_quicksort(
		directory.vector, directory.length, sizeof(void *), cmpft);
	ft_printdir(directory, flags);
	if (flags & RR_FLAG)
		directory.viter(&directory, &vprint_directories, 2, flags, cmpft);
	vector.destructor(&directory);
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
	files = vector.map(argv, (size_t)argc, sizeof(char *), &get_file_entry);
	ft_quicksort(files.vector, files.length, sizeof(void *), cmpft);
	files.iter(&files, &print_errors);
	files.iter(&files, &print_files);
	files.viter(&files, &vprint_directories, argc, flags, cmpft);
	vector.destructor(&files);
	return (0);
}
