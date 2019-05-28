
/*
**  Ft_ls -- Core Function(s).
*/

#include "ft_ls.h"

/*
**    NAME
**         ft_print_dir -- print all entries of a directory
**
**    SYNOPSIS
**         #include <libft.h>
**
**         void
**         ft_print_dir(t_vector directory, uint64_t flags);
**
**    PARAMETERS
**
**         t_vector directory     Brief
**
**         uint64_t flags         Brief
**
**    DESCRIPTION
**         Description.
**
**    RETURN VALUES
**         If successful returns 0; otherwise -1.
*/

void			ft_print_dir(t_vector directory, uint64_t flags)
{
	/* TODO : kev -- print all entry names (and corresponding info based on flags) */
	(void)directory;
	(void)flags;
	return ;
}

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

t_vector		ft_getdir(const char dirname[PATHMAX])
{
/* TODO : Aymen -- add functionality to ft_getdirectory function so that it returns a vector with */
/*                 t_file struct containing all needed information for each file/dir */

	t_vector	directory;
	DIR			*dirdes;

	directory = vector.empty(NULL);
	dirdes = opendir(dirname);
	if (dirdes != NULL)
	{
		directory = ft_getdir(dirdes);
		closedir(dirdes);
	}
	else
		perror(NULL);
	return (directory);
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

void	ft_listdir(const char dirname[PATHMAX], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	t_vector	directory;
	size_t		i;

	directory = ft_getdirectory(dirname);
	if (directory.vector)
	{
		ft_quicksort(
			directory.vector, directory.length, sizeof(void *), cmpft);
		print_directory(directory, flags);
		if (flags & RR_FLAG)
		{
			i = 0;
			while (i < directory.length)
			{
				if (((t_file *)directory.vector)[i].type == DIRECTORY)
					ft_listdir(((t_file *)directory.vector)[i].name, flags, cmpft);
				++i;
			}
		}
		vector.destructor(&directory);
	}
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
**         ft_ls(int ac, const char *av[], uint64_t flags,
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

int		ft_ls(int ac, const char *av[], uint64_t flags,
			int (*cmpft)(void *, void *))
{
	if (!av || ! cmpft)
		return (-1);
	if (av && *av)
	{
		/* TODO: aymen - implement the input into 3: errors, files & directories */
	}
	else
		ft_listdir("./", flags, cmpft);
	return (0);
}